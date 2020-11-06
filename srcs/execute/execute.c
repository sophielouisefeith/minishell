/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:18 by sfeith        #+#    #+#                 */
/*   Updated: 2020/11/06 17:52:14 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <fcntl.h>
#include <sys/wait.h>

static void		invoke_another_program(t_command **command, t_env **envb)
{
	int			pid;
	int			status;
	char		**array;

	signal(SIGINT, signal_reset);
	signal(SIGQUIT, signal_reset);
	array = env_ll_to_array(*envb);
	pid = fork();
	if (pid == -1)
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	if (pid == 0)
	{
		execve((*command)->array[0], (*command)->array, array);
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
		free_array(array);
	}
}

void			builtin_another_program(t_command **command, t_env **envb)
{
	if ((*command)->builtin == builtin_no || (*command)->builtin == executable)
		invoke_another_program(command, envb);
	if ((*command)->builtin != builtin_no_com && (*command)->builtin !=
			builtin_no && (*command)->builtin != executable)
		execute_builtin(command, envb);
}

static void		determine_fdout(t_command **command, t_execute **exe,
									t_env **envb, int i)
{
	if (i == (*exe)->len_list - 1)
		(*exe)->fdout = fill_fdout((*command)->output, (*exe)->tmpout);
	else if ((*command)->sem && (*command)->output)
	{
		execute_output(command, exe, envb);
		(*exe)->fdout = dup((*exe)->tmpout);
	}
	else if ((*command)->pipe_after)
	{
		if ((*command)->pipe_after && (*command)->output)
			execute_output(command, exe, envb);
		pipe((*exe)->fdpipe);
		(*exe)->fdout = (*exe)->fdpipe[1];
		(*exe)->fdin = (*exe)->fdpipe[0];
	}
	else
		(*exe)->fdout = dup((*exe)->tmpout);
	dup2((*exe)->fdout, 1);
	close((*exe)->fdout);
}

static int		determine_fdin(t_command *command, t_execute **exe)
{
	if (command->input)
	{
		(*exe)->fdin = open(command->input->str_input, O_RDONLY);
		if ((*exe)->fdin == -1)
		{
			errno = ENOENT;
			return (errno_error(command->input->str_input, command));
		}
	}
	dup2((*exe)->fdin, 0);
	close((*exe)->fdin);
	return (0);
}

void			*execute(t_command **command, t_env **envb)
{
	t_execute	*exe;
	int			res;

	initialise_execute(*command, &exe);
	while (exe->i < exe->len_list)
	{
		complete_path(command, *envb);
		res = determine_fdin(*command, &exe);
		if (res == 3)
			return (clean_exit_execute(&exe));
		check_specials(command, *envb);
		if (g_own_exit != 999 && (*command)->builtin == 0 && (*command)->array)
			error_command((*command)->array[0], 1, *command);
		else
			g_own_exit = 0;
		determine_fdout(command, &exe, envb, exe->i);
		if (!(((*command)->sem || (*command)->pipe_after) &&
			(*command)->output))
			builtin_another_program(command, envb);
		if ((*command)->sem)
			exe->fdin = dup(exe->tmpin);
		*command = (*command)->next_command;
		exe->i++;
	}
	return (clean_exit_execute(&exe));
}
