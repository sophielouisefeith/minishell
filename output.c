/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 09:30:21 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/03 13:25:52 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_output			*ll_new_node_output(void *content, int token_output)
{
	t_output		*new;

	new = (t_output *)malloc(sizeof(t_output));
	if (!new)
		return (0);
	new->str_output = content;
	new->token_output = token_output;
	new->next_output = NULL;
	return (new);
}

void			ll_lstadd_back_output(t_output **head_output, t_output *new_output)
{
	t_output		*list_output;

	list_output = *head_output;
	if (list_output)
	{
		while (list_output->next_output)
			list_output = list_output->next_output;
		list_output->next_output = new_output;
	}
	else
		*head_output = new_output;
}

void            output_fill(t_lexer **head)
{
    int                     token_output;
    t_output                output;
    t_output                *output_head; 				//head
    t_output                *tmp_output;

 
    output_head = NULL;
    token_output = check_token((*head)->str);
    *head = (*head)->next;
    tmp_output = ll_new_node_output((*head)->str, token_output);
	ll_lstadd_back_output(&output_head, tmp_output);
}
