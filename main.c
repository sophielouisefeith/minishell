/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/10 11:19:26 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void			lexer_parser_executer(char *line, int i)
{
	t_lexer		*sort;
	t_command 	*command;								
	int			count;									//naam
	int 		k;										//naam

	k = 0;
	count = 0;
	sort = NULL;
	command = NULL;
	if (line[i] != '\0')
		lexer(&sort, line);
	while (sort)
	{
		k = parser(&sort, &command, count);				//naam count en k
		if (k == 1)
			count = 1;
		else
			count = 0;
		if (sort)
			sort = sort->next;
	}
	//free_array(array);
	// execute();
// LEXER TESTER
	// t_lexer		*sort_list;
	// sort_list = sort;
	// while (sort_list)
	// {
	// 	printf("node-str = [%s], token_general = [%d]\n", sort_list->str, sort_list->token[token_general]);
	// 	sort_list = sort_list->next;	
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
		while (command->output)
		{
			printf("node---str_output[%s]\n", command->output->str_output);
			command->output = command->output->next_output;
		}
		while (command->input)
		{
			printf("node---str_intput[%s]\n", command->input->str_input);
			command->input = command->input->next_input;
		}
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
		if (ret == -1)
			error_free(errno);
		lexer_parser_executer(line, i);
		free(line);
		line = NULL;
	}
}
