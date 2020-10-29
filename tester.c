/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   tester.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 10:46:14 by maran         #+#    #+#                 */
/*   Updated: 2020/10/29 11:35:42 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** LATER VERWIJDEREN
** Changelog:
	- Toegevoegd:
	copy_output en copy_input
*/

void            tester(t_lexer *sort, t_command *command)
{
    // LEXER TESTER
	// printf("--------------------Node------------------------------:\n");
	// while (sort)
	// {
	// 	printf("node-str = [%s], token_general = [%d]\n", sort->str, sort->token[token_general]);
	// 	sort = sort->next_sort;	
	// }
	(void)sort;
//PARSER TESTER
	t_output	*copy_output;
	t_input		*copy_input;
	int 		n;

	copy_output = command->output;
	copy_input = command->input;
	while (command)
	{
		n = 0;
		printf("--------------------Node------------------------------:\n");
		printf("node---builtin = [%d]\n", command->builtin);
    	printf("node---pipe before[%d]\n", command->pipe_before);
		printf("node---pipe after[%d]\n", command->pipe_after);
    	printf("node---sem[%d]\n", command->sem);
		while (copy_output)
		{
			printf("node---str_output[%s], token = [%d]\n", copy_output->str_output, copy_output->token);
			copy_output = copy_output->next_output;
		}
		while (copy_input)
		{
			printf("node---str_intput[%s]\n", copy_input->str_input);
			copy_input = copy_input->next_input;
		}
		if (command->array)
		{
			printf("command->array:\n");
			while (command->array[n])
			{
				printf("node-str[%d] = [%s]\n", n, command->array[n]);
				// printf("quote[%d] = [%d]\n", n, command->quote[n]);
				n++;
			}
		}
		printf("--------------------Einde Node------------------------:\n");
		command = command->next_command;
	}
}
