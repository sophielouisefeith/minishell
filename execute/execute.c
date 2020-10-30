/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/30 17:18:40 by SophieLouis   ########   odam.nl         */
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
		printf("pid == null\n");
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
	//printf("--------------builtotgerprogram_exceute \n");
	if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
		invoke_another_program(command, _env);
	if ((*command)->builtin != builtin_no_com && (*command)->builtin !=
			builtin_no && (*command)->builtin != executable)
		execute_builtin(command, _env);
}

static void		determine_fdout(t_command **command, t_execute **exe,
									t_env **_env, int i)
{
	//printf("--------------determine_fdout, execute\n");
	if (i == (*exe)->len_list - 1)
		(*exe)->fdout = fill_fdout((*command)->output, (*exe)->tmpout);
	else if ((*command)->sem && (*command)->output)
	{
	//	printf("output\n");
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

static int	determine_fdin(t_command *command, t_execute **exe)
{
	//printf("--------------determine_fdin, execute\n");
	if (command->input)
	{
		(*exe)->fdin = open(command->input->str_input, O_RDONLY);
		if ((*exe)->fdin == -1)
		{
		//	printf("determine_fdin\n");
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
	//printf("--------------complete_path_execute\n");
	char		*str_before;
	char 		*tmp;

	if ((*command)->builtin == builtin_no && (*command)->array)
	{
		
		str_before = ft_strdup((*command)->array[0]);					//alleen 0?
		tmp = ft_strdup((*command)->array[0]);
		free((*command)->array[0]);
		(*command)->array[0]= NULL;
		(*command)->array[0] = check_path(_env, tmp);
	//	printf("command[%s]\n", (*command)->array[0]);
		if((*command)->array[0]== NULL )
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
//	printf("------------execute_\n");
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
			//printf("res = 0 \n");
			//close_execute(&exe);
			//free(exe);	//LEAKS
			return(0);    // or own exit status op 0 zodat hij eruit klapt 
		}
		check_specials(command, *_env);  //res = 
		// if(!executable)
		// {
		// 	printf("executable is aan\n");
		// 	error_command("/", 3);
		// 	return(0);
		// }
		// else
			
		
		// tester(NULL, *command);
		if (g_own_exit != 999 && (*command)->builtin == builtin_no_com && (*command)->array)				//new		//(*command)->array voor pwd ; $POEP ; echo doei
			{
				//printf("execute_error_command welke foutmelding moet hier komen?\n");
				//printf("commandarray_execut[%s]\n",(*command)->array[0]);
				error_command((*command)->array[0], 1, *command);
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

/*
29/10: verwijderd ivm pwd ; $POEP ; echo doei

			// if ((*command)->builtin == builtin_no_com && !((*command)->sem || (*command)->pipe_after) && (!(*command)->array || !(*command)->array[0]))		//M: Welke case komt dit voor? anders liever verwijderen. S: $POEP komt het voor
			// {																																				// Sem en pipe toegevoegd voor pwd ; $POEP ; echo doei
			// 	free(exe);
			// 	return (0);
			// }

*/