/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/26 17:12:58 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** We loop through sort in parser, we make a copy beforehand.
** So when we start free'ing, we start at the first node of sort and not at the end.
** 
** Changelog:
	- Removed k
	//sort = (char **)malloc(() * sizeof(char *)); // struct mallocen
	//command = (char **)malloc(() * sizeof(char *)); struct mallocen
	//changed next to  next_sort
	//puted tester above the free otherwise segg
	- added: Copy of sort!
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
		pipe_status = parser(&sort, &command, pipe_status);
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
*/

int					main(int argc, char **argv, char **env)
{
	t_env		*_env;	
	char		*line;
	int			ret;
	int 		i;

	ret = 1;
	_env = save_env(env);	
	while (ret > 0)
	{
		i = 0;
		write(1, "$ ", 2);
		ret = get_next_line(0, &line);
		//if (ret == -1)
			//error(2, line); // ---------------here we say  No such file or directory
		lexer_parser_executer(line, i, &_env);
		free(line);
		line = NULL;
	}
	return (0);
}
