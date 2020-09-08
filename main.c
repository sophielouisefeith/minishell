/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/09/08 20:36:36 by maran         ########   odam.nl         */
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

static void			lexer_parser_executer(char *line, int i, t_env **_env)
{
	t_lexer		*sort;
	t_lexer		*sort_copy;
	t_command 	*command;
	int			pipe_status;

	pipe_status = 0;
	sort = NULL;
	command = NULL;
	if (line[i] != '\0')
		lexer(&sort, line);
	sort_copy = sort;
	while (sort)
	{
		pipe_status = parser(&sort, &command, pipe_status, _env);
		if (sort)
			sort = sort->next_sort;
	}
	// tester(sort, command);
	
	//FREE LEXER
	free_list_lexer(&sort_copy);
	
	//EXECUTOR
	execute(&command, _env);

	//FREE COMMAND
	free_list_parser(&command);
}

/*
** Spaces before commands or returns are allowed.
** Return key: prompt on a new line
**
** if (line[i] != '\0') --> checks if line is empty.
** If not execute, else new prompt.
*/ 

/*
** CTRL C:
	- The interrupt signal, sends SIGINT to the job running in the foreground. --> Dus stopt echt sleep, maar sluit niet heel de shell.
	- exit_code 130
** CTRL \:
	- QUIT signal-  by default terminates an application
	- lijkt hetzelfde als ctrl-c, behalve (^\Quit: 3)
	- exit_code 131.
** CTRL D (End of File):
	- lijkt running proces af te ronden en sluit dan de shell
	- exit_code 0
*/

static void			ctrl_d(int ret)
{
	if (ret == 0)
	{
		printf("exit\n");
		exit(0);
	}
}

void 		sighandler(int signum)
{
	if (signum == SIGINT)
		write(1, "\n", 1);
	if (signum == SIGQUIT)
		printf("Quit: 3\n");
}

int					main(int argc, char **argv, char **env)
{
		
	t_env		*_env;	
	char		*line;
	int			ret;
	int 		i;


	ret = 1;
	_env = save_env(env);
 	signal(SIGINT, sighandler);		// CTRL C
	signal(SIGQUIT, sighandler);	// CTRL backslash
	while (ret > 0)
	{
		i = 0;
		write(1, COLOR_PROMPT, 24);
		ret = get_next_line(0, &line);
		if (ret <= 0)
			ctrl_d(ret);
		//if (ret == -1)
			//error(2, line); // ---------------here we say  No such file or directory
		if (line[i] != '\0')
			lexer_parser_executer(line, i, &_env);
		
		free(line);
		line = NULL;
	}
	free_env(_env);												//new
	return (0);
}
