/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pipe_TEST.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/05 12:22:16 by maran         #+#    #+#                 */
/*   Updated: 2020/11/05 12:56:58 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		count_pipes(t_command *cmd_list)
{
	int n;

	n = 0;
	while (cmd_list && !cmd_list->sem)
	{
		if (cmd_list->pipe_after)
			n++;
		cmd_list = cmd_list->next_command;
	}
	return (n);
}

int			setup_pipes(int n_pipes, int **fds)
{
	int i;

	*fds = malloc(sizeof(int) * (n_pipes * 2));
	if (!(*fds))
		return (1);
	i = 0;
	while (i < n_pipes)
	{
		if (pipe((*fds) + i * 2) < 0)
		{
			PRINTF("PIPE ERROR\n");		// err_msg(NULL, NULL, strerror(errno));
			free((*fds));
			return (1);
		}
		i++;
	}
	return (0);
}

void	check_type(t_command *ptr, int *type)
{
	while (ptr && !ptr->pipe_after && !ptr->sem)
		ptr = ptr->next_command;
	// if (ptr && ptr->command == PIPE_PLUS)
	// 	*type = 1;
	// else
		*type = 0;
}


t_node		*clean_exit_pipe(t_node **ptr, int exit_code, int *fds)
{
	if (exit_code != 0)
		err_msg(NULL, NULL, strerror(errno));
	g_exitcode = exit_code;
	free(fds);
	while (*ptr && (*ptr)->command != SEMICOLON)
		*ptr = (*ptr)->next;
	return (*ptr);
}

static int	child_process(int cmd_index, int *fds, int n_pipes, t_command **ptr)
{
	int pipe_plus;

	check_type(*ptr, &pipe_plus);
	if (cmd_index != 0)
		if (dup2(fds[(cmd_index - 1) * 2], 0) < 0)
			return (-1);
	if (cmd_index != n_pipes)
	{
		if (dup2(fds[cmd_index * 2 + 1], 1) < 0)
			return (-1);
		if (pipe_plus)
			if (dup2(fds[cmd_index * 2 + 1], 2) < 0)
				return (-1);
	}
	close_fds(n_pipes, fds);
	return (0);
}

t_command		*execute_in_pipe(t_command **ptr, int npipe, t_env **list, int *fds)
{
	int	pid;
	int cmd_index;

	cmd_index = 0;
	while (*ptr && !(*ptr)->sem) // && (*ptr)->command != REDIR)
	{
		pid = fork();
		if (pid == -1)
			printf("PID ERROR\n");
		else if (pid == 0)				//child
		{
			if (child_process(cmd_index, fds, npipe, ptr) == -1)
				return (clean_exit_pipe(ptr, 9, fds));
			execute_cmd(*ptr, list);
			exit(g_exitcode);
		}
		cmd_index = skip_to_cmd(ptr, cmd_index);
	}
	close_fds(npipe, fds);
	while (wait(NULL) > 0)
		;
	return (clean_exit_pipe(ptr, 0, fds));
}

void			check_pipes(t_command *command, t_env **envb)
{
	t_command		*ptr;
	int		*fds;

	ptr = command;
	int n_pipes = count_pipes(command);
	printf("Pipes = [%d]\n", n_pipes);
	if (n_pipes)
		if (setup_pipes(n_pipes, &fds))			//pipe[fds] staan open
			return (NULL);
		execute_in_pipe(&ptr, n_pipes, envb, *fds);
	
}
