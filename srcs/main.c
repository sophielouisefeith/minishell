/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/11/01 20:13:57 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/get_next_line/get_next_line.h"
#include <signal.h>
#define COLOR_PROMPT	"\033[1;34mminishell-$ \033[0m"

void			lexer_parser_executer(char *line, t_env **envb)
{
	t_lexer		*sort;
	t_lexer		*sort_copy;
	t_command	*command;
	t_command	*command_copy;
	int			pipe_status;

	pipe_status = 0;
	sort = NULL;
	command = NULL;
	lexer(&sort, line);
	sort_copy = sort;
	while (sort && pipe_status != 3 && g_own_exit != 3)
	{
		pipe_status = parser(&sort, &command, pipe_status);
		if (pipe_status == 3)
			g_own_exit = 0;
		if (sort)
			sort = sort->next_sort;
	}
	command_copy = command;
	free_list_lexer(&sort_copy);
	if (g_own_exit == 0)
		execute(&command, envb);
	free_list_parser(&command_copy);
}

static void		prep_start(void)
{
	signal(SIGQUIT, sighandler);
	signal(SIGINT, sighandler);
	write(1, COLOR_PROMPT, 23);
}

int				main(int argc, char **argv, char **env)
{
	t_env		*envb;
	char		*line;
	int			ret;

	ret = 1;
	envb = saveenvb(env);
	(void)argc;
	(void)argv;
	while (ret > 0)
	{
		prep_start();
		ret = get_next_line(0, &line);
		if (ret == 0)
			ctrl_d();
		if (ret == -1)
			set_exit_status();
		if (line[0] != '\0')
			lexer_parser_executer(line, &envb);
		g_own_exit = 0;
		free(line);
		line = NULL;
	}
	freeenvb(envb);
	return (0);
}