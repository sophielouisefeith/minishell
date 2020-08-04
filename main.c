/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/04 12:06:07 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void		lexer_parser_executer(char *line, int i)
{
	t_lexer		*lex_head;
	t_command 	*command; 
	int			count;
	int 		k;
	
	k = 0;
	count = 0;
	lex_head = NULL;
	command = NULL;
	if (line[i] != '\0')
		lexer(&lex_head, line);
	while (lex_head)
	{
		k = transform(&lex_head, &command, count);
		if (k == 1)
			count = 1;
		else
			count = 0;
		if (lex_head)
			lex_head = lex_head->next;
	}
	// execute();
// LEXER TESTER
	// while (lex_head)
	// {
	// 	printf("node-str = [%s]\n", lex_head->str);
	// 	lex_head = lex_head->next;	
	// }
//PARSER TESTER
	int n;
	while (command)
	{
		n = 0;
		printf("--------------------Node------------------------------:\n");
		printf("node---builtin = [%d]\n", command->builtin);
    	printf("node---pipe before[%d]\n", command->pipe_before);
		printf("node---pipe after[%d]\n", command->pipe_after);
    	printf("node---sem[%d]\n", command->sem);
		while (command->array[n])
		{
			printf("node-str[%d] = [%s]\n", n, command->array[n]);
			n++;
		}
		printf("--------------------Einde Node------------------------:\n");
		command = command->next;
	}
}


/*
** Spaces before commands or returns are allowed.
** Return key: prompt on a new line
*/

int				main(int argc, char **argv)
{
	char	*line;
	int		ret;
	int 	i;
	ret = 1;
	while (ret > 0)
	{
		i = 0;
		write(1, "$ ", 2);
		ret = get_next_line(0, &line);
		// if (ret == -1)
		// 	error();
		lexer_parser_executer(line, i);
		free(line);
		line = NULL;
	}
}
