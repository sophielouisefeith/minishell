/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/10/22 17:55:18 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>

#define COLOR_PROMPT	"\033[1;34mminishell-$ \033[0m"

// int		g_exit_status;

/*
** \033				Octal value of ESC (escape sequence)
** [1				Bold
** ;				Divider
** 34				Color code (blue)
** m				Ending char
** minishell-$		Text
** \033				ESC
** [0m				reset
*/

/*
** We loop through sort in parser, we make a copy beforehand.
** So when we start free'ing, we start at the first node of sort and not at the end.
** TO DO:
	- Wss ook nog een copy van command nodig na execute. Later naar kijken.
*/

void			lexer_parser_executer(char *line, int i, t_env **_env)
{
	t_lexer		*sort;
	t_lexer		*sort_copy;
	t_command 	*command;
	t_command	*command_copy;
	int			pipe_status;

	pipe_status = 0;
	sort = NULL;
	command = NULL;
	if (line[i] != '\0')
		lexer(&sort, line);
	sort_copy = sort;
	while (sort && g_own_exit == 0)
	{
		pipe_status = parser(&sort, &command, pipe_status, _env);
		//if(pipe_status == 12)// slaat nergens op even voor eigen dingen
			//printf("malloc failed\n"); /// dit is overbodig word al een error gegeven en gefreet omdat g_own_exit =1 
		if (sort)
			sort = sort->next_sort;
	}
	// tester(sort, command);
	//FREE LEXER
	command_copy = command;
	free_list_lexer(&sort_copy);

	// //EXECUTOR
		if (g_own_exit == 0)
	execute(&command, _env);
	// else
	// {
	// 	free(lexer);
	// }

	// //FREE COMMAND
	free_list_parser(&command_copy);		//LEAKS
	//  free_list_executer();
}

/*
** Spaces before commands or returns are allowed.
** Return key: prompt on a new line
**
** if (line[i] != '\0') --> checks if line is empty.
** If not execute, else new prompt.
*/

int					main(int argc, char **argv, char **env)
{	
	t_env		*_env;	
	char		*line;
	int			ret;

	ret = 1;
	_env = save_env(env);
	while (ret > 0)
	{
		signal(SIGQUIT, sighandler);
 		signal(SIGINT, sighandler);
		write(1, COLOR_PROMPT, 23);
		ret = get_next_line(0, &line);
		if (ret == 0)
			ctrl_d();
		if (ret == -1)
			set_exit_status(); ///-----new // gaat het hier nou mis met./ nee want het is een executable 
		if (line[0] != '\0')
			lexer_parser_executer(line, 0, &_env);
		g_exit_status = (g_own_exit > 0 && g_own_exit != 999) ?
			g_own_exit : g_exit_status;
		g_own_exit = 0;
		free(line);
		line = NULL;
	}
	free_env(_env);
	return (0);
}
