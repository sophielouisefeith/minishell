/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/29 13:48:20 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <fcntl.h>

/*
** TO DO:
	- //welke exit code? bij errno_error
	- if ((*command)->builtin == builtin_no_com)		//Twijfel of dit goed gaat. Toegevoegd vanwege $echo hallo
*/

/*
** Waitpid: suspends execution of the calling process until a child specified
** by pid argument has changed state.
** WIFEXITED(status): returns true if the child terminated normally.
** WEXITSTATUS(status): returns the exit status of the child. This macro should
** be employed only if WIFEXITED returned true.
*/

static void		invoke_another_program(t_command **command, t_env **_env)
{
	int		pid;
	int 	status;

	signal(SIGINT, signal_reset);							//new vw signals
	signal(SIGQUIT, signal_reset);
	pid = fork();
	if (pid == -1)
	{
		
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	}
	if (pid == 0)
	{
		execve((*command)->array[0], (*command)->array,
			env_ll_to_array(*_env));
		// if(builtin_type == executable) //lelijke oplssoing voor foutmelding
		// 	errno = 21;
		errno_error((*command)->array[0]);									// --> 1 van de foutmeldingen van unset PATH ; ls
		exit(g_exit_status);
	}
	if (pid != 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status)) 							///NEW vw signals
			sighandler_execve(WTERMSIG(status));
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

/*
** MOE:
	if ((*command)->array && (*command)->array[0])
*/

void			builtin_another_program(t_command **command, t_env **_env)
{
	if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
		invoke_another_program(command, _env);
	if ((*command)->builtin != builtin_no_com && (*command)->builtin !=
			builtin_no && (*command)->builtin != executable)
		execute_builtin(command, _env);
}

static void		determine_fdout(t_command **command, t_execute **exe,
									t_env **_env, int i)
{
	if (i == (*exe)->len_list - 1)
		(*exe)->fdout = fill_fdout((*command)->output, (*exe)->tmpout);
	else if ((*command)->sem && (*command)->output)
	{
		execute_output(command, exe, _env);
		(*exe)->fdout = dup((*exe)->tmpout);
	}
	else if ((*command)->pipe_after)
	{
		if ((*command)->pipe_after && (*command)->output)
			execute_output(command, exe, _env);
		pipe((*exe)->fdpipe);
		(*exe)->fdout = (*exe)->fdpipe[1];
		(*exe)->fdin  = (*exe)->fdpipe[0];
	}
	else
		(*exe)->fdout = dup((*exe)->tmpout);
	dup2((*exe)->fdout,1);
	close((*exe)->fdout);
}

static void		*determine_fdin(t_command *command, t_execute **exe)
{
	if (command->input)
	{
		(*exe)->fdin = open(command->input->str_input, O_RDONLY);
		if ((*exe)->fdin == -1)
		{
			return (errno = ENOENT, errno_error(command->input->str_input));
		}
	}
	dup2((*exe)->fdin, 0);
	close((*exe)->fdin);
	return (0);
}

/*
** MOE:
		g_own_exit = 0;				//Welke de g_own?

	// if (((*command)->builtin == builtin_no_com && 
		// 		(!(*command)->array || !(*command)->array[0]) &&
		// 			 (!(*command)->pipe_after && !(*command)->sem)) ||  g_own_exit != 0)		//uitgecomment

LAATSTE VERSIE VOOR fixes 23/10 : ga dan terug naar ---> 23/10 fixed capital commands, removed MOE
		// printf("array[0] = [%p][%s] -> &[%p]\n", (*command)->array[0], (*command)->array[0], &(*command)->array[0]);
*/




void			complete_path(t_command **command, t_env *_env)
{
	char		*str_before;
	char 		*tmp;

	// printf("in complete path\n");
	if ((*command)->builtin == builtin_no && (*command)->builtin && (*command)->array[0])
	{
		// printf("in complete path1\n");
		str_before = ft_strdup((*command)->array[0]);					//alleen 0?
		tmp = ft_strdup((*command)->array[0]);
		free((*command)->array[0]);
		(*command)->array[0]= NULL;
		// printf("in complete path2\n");
		(*command)->array[0] = check_path(_env, tmp);					
		// printf("in complete path3\n");
		// if((*sort)->str == NULL)
		// 	return(ENOMEM);
		// printf("[%s] en [%s]\n", str_before, (*command)->array[0]);
		if (!ft_strcmp(str_before, (*command)->array[0]))
			(*command)->builtin = builtin_no_com;
		free(str_before);
	}
	// printf("uit complete path\n");
}


void			*execute(t_command **command, t_env **_env)
{
	t_execute	*exe;
	exe = (t_execute *)malloc(sizeof(t_execute));
	if (!exe)
		malloc_fail();
	initialise_execute(*command, &exe);
	while (exe->i < exe->len_list)
	{
		// tester(NULL, *command);
		// printf("0\n");
		complete_path(command, *_env);
		// printf("1\n");
		determine_fdin(*command, &exe);
		check_specials(command, *_env);
		if (g_own_exit != 999) 
		{
			if ((*command)->builtin == builtin_no_com && (!(*command)->array || !(*command)->array[0]))		//M: Welke case komt dit voor? anders liever verwijderen. S: $POEP komt het voor
			{
				free(exe);
				return (0);
			}
			if ((*command)->builtin == builtin_no_com)				//new
				error_command((*command)->array[0]);
		}
		else			//reset g_own
			g_own_exit = 0;										//new
		determine_fdout(command, &exe, _env, exe->i);
		if (!(((*command)->sem || (*command)->pipe_after) && (*command)->output))
			builtin_another_program(command, _env);
		if ((*command)->sem)
		{
			//printf("sem\n");
			exe->fdin = dup(exe->tmpin);
		}
		*command = (*command)->next_command;
		exe->i++;
	}
	close_execute(&exe);
	free(exe);	//LEAKS
	return (0);
}
