/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/10/31 14:51:37 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "../libft/get_next_line/get_next_line.h"
#include <signal.h>
#define COLOR_PROMPT	"\033[1;34mminishell-$ \033[0m"

void			lexer_parser_executer(char *line, t_env **_env)
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
	while (sort && pipe_status != 3 && g_own_exit!= 3) // && g_own_exit == 0)				//MOET DEZE DAN OOK WEER TERUG?
	{
		pipe_status = parser(&sort, &command, pipe_status);
		//if(pipe_status == 3) /// nu voor de dubbele ;										//NEW na pull, niet gecleaned
		//	printf("je mag er nu uit\n");
		//if(pipe_status == 12)// slaat nergens op even voor eigen dingen
			//printf("malloc failed\n"); /// dit is overbodig word al een error gegeven en gefreet omdat g_own_exit =1 
		if (sort)
			sort = sort->next_sort;
	}
	command_copy = command;
	free_list_lexer(&sort_copy);
	if (g_own_exit == 0)						
		execute(&command, _env);
	free_list_parser(&command_copy);
}

//Nog te lang. Wacht op error afhandeling.

int				main(int argc, char **argv, char **env)
{
	t_env		*_env;	
	char		*line;
	int			ret;

	ret = 1;
	_env = save_env(env);
	(void)argc;
	(void)argv;
	while (ret > 0)
	{
		signal(SIGQUIT, sighandler);
 		signal(SIGINT, sighandler);
		write(1, COLOR_PROMPT, 23);
		ret = get_next_line(0, &line);
		if (ret == 0)
			ctrl_d();
		if (ret == -1)
			set_exit_status();						// M: ik denk dat we kunnen breaken hier instead.
		if (line[0] != '\0')
			lexer_parser_executer(line, &_env);
		g_own_exit = 0;
		free(line);
		line = NULL;
	}
	free_env(_env);
	return (0);
}
