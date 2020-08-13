/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/13 10:56:44 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changelog:
	- Removed k
	//sort = (char **)malloc(() * sizeof(char *)); // struct mallocen
	//command = (char **)malloc(() * sizeof(char *)); struct mallocen
*/

static void			lexer_parser_executer(char *line, int i)
{
	t_lexer		*sort;
	t_command 	*command;								
	int			pipe_status;

	pipe_status = 0;
	sort = NULL;
	command = NULL;
	if (line[i] != '\0')
		lexer(&sort, line);
	while (sort)
	{
		pipe_status = parser(&sort, &command, pipe_status);
		if (sort)
			sort = sort->next;
	}
	//FREE LEXER
	// free_list(&sort, NULL);						// kunnen na de parser heel de lexer freen
	//EXECUTOR
	// execute()
	//FREE COMMAND
	//free_list(&sort, command);
	tester(sort, command);
}

/*
** Spaces before commands or returns are allowed.
** Return key: prompt on a new line
*/

int					main(int argc, char **argv)
{
	char		*line;
	int			ret;
	int 		i;

	
	ret = 1;
	while (ret > 0)
	{
		i = 0;
		write(1, "$ ", 2);
		ret = get_next_line(0, &line);
		//if (ret == -1)
			//error(2, line); // ---------------here we say  No such file or directory
		lexer_parser_executer(line, i);
		free(line);
		line = NULL;
	}
}
