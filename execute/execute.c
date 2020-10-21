/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/21 19:01:54 by maran         ########   odam.nl         */
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
	int 	builtin_type;

	pid = fork();
	if (pid == -1)
		write(1, strerror(errno), ft_strlen(strerror(errno)));//printf("[%s]", strerror(errno));
	if (pid == 0)
	{
		//printf("is pidd 0\n");
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
	if ((*command)->builtin == builtin_no_com)
	{
		if(g_exit_status != 127)   // dirty $USER solution
			error_command((*command)->array[0]);
		else
		{
			//exit(0); // even oppassen of dit dan goed gaat met freen.
			g_own_exit = 2; // dit even kijken als dit zo is dan execute freen 
		}
		
	}
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
			return (errno = ENOENT, (command->input->str_input));
	}
	dup2((*exe)->fdin, 0);
	close((*exe)->fdin);
	return (0);
}

void			*execute(t_command **command, t_env **_env)
{
	t_execute	*exe;

	exe = (t_execute *)malloc(sizeof(t_execute));
	if(!exe)
		malloc_fail(errno = ENOMEM);
	initialise_execute(*command, &exe);
	while (exe->i < exe->len_list)
	{
		determine_fdin(*command, &exe);
		check_specials(command, *_env);
		if (((*command)->builtin == builtin_no_com && (!(*command)->array || !(*command)->array[0])) || g_own_exit != 0)
		{
			free(exe);		//LEAKS
			return (0);
		}
		determine_fdout(command, &exe, _env, exe->i);
		if (!(((*command)->sem || (*command)->pipe_after) &&
				(*command)->output))
			builtin_another_program(command, _env);
		if ((*command)->sem)
			exe->fdin = dup(exe->tmpin);
		*command = (*command)->next_command;
		exe->i++;
	}
	close_execute(&exe);
	free(exe);	//LEAKS
	return (0);
}
