/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 10:46:14 by maran         #+#    #+#                 */
/*   Updated: 2020/08/13 10:54:35 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** LATER VERWIJDEREN
*/

void            tester(t_lexer *sort, t_command *command)
{
    // LEXER TESTER
	// while (sort)
	// {
	// 	printf("node-str = [%s], token_general = [%d]\n", sort->str, sort->token[token_general]);
	// 	sort = sort->next;	
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
		command = command->next_command;
	}
}
