/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/14 14:24:15 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changelog:
	- Removed k
	//sort = (char **)malloc(() * sizeof(char *)); // struct mallocen
	//command = (char **)malloc(() * sizeof(char *)); struct mallocen
	//changed next to  next_sort
	//puted tester above the free otherwise segg
*/

static void			lexer_parser_executer(char *line, int i)
{
	t_lexer		*sort;
	t_lexer		*sort_copy;
	t_command 	*command;
	t_command 	*command_copy;								
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
	command_copy = command;						
	// tester(sort_copy, command_copy);
	printf("---------output VOOR tester = [%p]\n",(command)->output);
	tester(sort, command);
	printf("---------output NA tester = [%p]\n",(command)->output);
	
	//FREE LEXER
	free_list_lexer(&sort_copy);   //niet met sort? Nee want die is verder geloopt in parser (misschien in parser copy meegeven)
	// free_list_lexer(&sort);
	
	//EXECUTOR
	// execute(&command);

	//FREE COMMAND
	free_list_parser(&command_copy);
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
	return (0);
}
