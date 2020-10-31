/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/31 22:12:50 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
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
	int			pid;
	int			status;

	signal(SIGINT, signal_reset);
	signal(SIGQUIT, signal_reset);
	pid = fork();
	if (pid == -1)
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	if (pid == 0)
	{
		execve((*command)->array[0], (*command)->array,
			env_ll_to_array(*_env));
		// if(builtin_type == executable) //lelijke oplssoing voor foutmelding
		// 	errno = 21;
		errno_error((*command)->array[0], *command);
		exit(g_exit_status);
	}
	if (pid != 0)
	{
		waitpid(pid, &status, 0);
		if (WIFSIGNALED(status))
			sighandler_execve(WTERMSIG(status));
		if (WIFEXITED(status))
			g_exit_status = WEXITSTATUS(status);
	}
}

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

static int		determine_fdin(t_command *command, t_execute **exe)
{
	if (command->input)
	{
		(*exe)->fdin = open(command->input->str_input, O_RDONLY);
		if ((*exe)->fdin == -1)
			return (errno = ENOENT, errno_error(command->input->str_input, command));
	}
	dup2((*exe)->fdin, 0);
	close((*exe)->fdin);
	return (0);
}

void			complete_path(t_command **command, t_env *_env)
{
	char		*str_before;
	char		*tmp;

	if ((*command)->builtin == builtin_no && (*command)->array)
	{
		str_before = ft_strdup((*command)->array[0]);
		tmp = ft_strdup((*command)->array[0]);
		free((*command)->array[0]);
		(*command)->array[0]= NULL;
		(*command)->array[0] = check_path(_env, tmp);
		if ((*command)->array[0]== NULL)
			error_command((*command)->array[0], 1, *command);
		// if((*sort)->str == NULL)
		// 	return(ENOMEM);
		if (!ft_strcmp(str_before, (*command)->array[0]))
			(*command)->builtin = builtin_no_com;
		free(str_before);
	}
}

void			*execute(t_command **command, t_env **_env)
{
	t_execute	*exe;
	int 		res;

	exe = (t_execute *)malloc(sizeof(t_execute));
	if (!exe)
		malloc_fail();
	initialise_execute(*command, &exe);
	while (exe->i < exe->len_list)
	{
		complete_path(command, *_env);
		res = determine_fdin(*command, &exe);
		if(res == 3) // 3 staast voor de return uit errno_error S: wel handig om dit voorbeeld nog even op te zoeken 
		{
			close_execute(&exe);
			free(exe);
			return(0);    // or own exit status op 0 zodat hij eruit klapt 
		}
		check_specials(command, *_env);  //res = 
		if (g_own_exit != 999 && (*command)->builtin == builtin_no_com && (*command)->array)
			error_command((*command)->array[0], 1, *command);
		else
			g_own_exit = 0;
		determine_fdout(command, &exe, _env, exe->i);
		if (!(((*command)->sem || (*command)->pipe_after) && (*command)->output))
			builtin_another_program(command, _env);
		if ((*command)->sem)
			exe->fdin = dup(exe->tmpin);
		*command = (*command)->next_command;
		exe->i++;
	}
	close_execute(&exe);
	free(exe);
	return (0);
}
