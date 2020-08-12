/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/12 16:59:56 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void			lexer_parser_executer(char *line, int i)
{
	t_lexer		*sort;
	t_command 	*command;								
	int			pipe_status;									//naam
	int 		k;
	void		*del;									//naam

	k = 0;
	pipe_status = 0;
	sort = NULL;
	command = NULL;
	//sort = (char **)malloc(() * sizeof(char *)); // struct mallocen
	//command = (char **)malloc(() * sizeof(char *)); struct mallocen
	if (line[i] != '\0')
		lexer(&sort, line);
	while (sort)
	{
		k = parser(&sort, &command, pipe_status);				//naam count en k
		if (k == 1)
			pipe_status = 1;
		else
			pipe_status = 0;
		if (sort)
			sort = sort->next;
	}
	free_list(&sort, NULL);						// kunnen na de parser heel de lexer freen
	//free(lexer);
	//executor
	//free_list_command(&command);
	// free_list_command(&command, del);
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
			printf("node---str_output[%s], token = [%d]\n", command->output->str_output, command->output->token);
			command->output = command->output->next;
		}
		while (command->input)
		{
			printf("node---str_intput[%s]\n", command->input->str_input);
			command->input = command->input->next;
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
		//if (ret == -1)
			//error(2, line); // ---------------here we say  No such file or directory
		lexer_parser_executer(line, i);
		free(line);
		line = NULL;
	}
}
