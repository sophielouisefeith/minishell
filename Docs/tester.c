/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maran <maran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/13 10:46:14 by maran             #+#    #+#             */
/*   Updated: 2020/11/04 17:01:49 by maran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** LATER VERWIJDEREN
*/

void            tester(t_lexer *sort, t_command *command)
{
    // LEXER TESTER
	// (void)command;
	// printf("--------------------Node------------------------------:\n");
	// while (sort)
	// {
	// 	printf("node-str = [%s]\n", sort->str);
	// 	printf("token_null= [%d]\n", sort->token[token_null]);
	// 	printf("token_general= [%d]\n", sort->token[token_general]);
	// 	printf("token_whitespace= [%d]\n", sort->token[token_whitespace]);
	// 	printf("token_quote= [%d]\n", sort->token[token_quote]);
	// 	printf("token_dquote= [%d]\n", sort->token[token_dquote]);
	// 	printf("token_pipe= [%d]\n", sort->token[token_pipe]);
	// 	printf("token_semicolon= [%d]\n", sort->token[token_semicolon]);
	// 	printf("token_redirection= [%d]\n", sort->token[token_redirection]);
	// 	printf("token_redi >= [%d]\n", sort->token[token_redirection_greater]);
	// 	printf("token_redi < = [%d]\n", sort->token[token_redirection_lesser]);
	// 	printf("token_redi >>= [%d]\n", sort->token[token_redirection_dgreater]);
	// 	printf("token_null= [%d]\n", sort->token[token_dollar]);
	// 	printf("--------------------Eind Node------------------------------:\n");
	// 	sort = sort->next_sort;	
	// }
//PARSER TESTER
	t_output	*copy_output;
	t_input		*copy_input;
	int 		n;

	(void)sort;
	copy_output = command->output;
	copy_input = command->input;
	while (command)
	{
		printf("TESTER: command\n");
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
