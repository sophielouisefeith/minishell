/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 09:30:21 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/07 17:58:41 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_output			*ll_new_node_output(void *content, int token_output)
{
	t_output		*new;

	new = (t_output *)malloc(sizeof(t_output));
	if(!new)
		error_free(errno);;
	new->str_output = content;
	new->token_output = token_output;
	new->next_output = NULL;
	return (new);
}

static void			ll_lstadd_back_output(t_output **head_output, t_output *new_output)
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

void            output_fill(t_lexer **head, t_command **tmp)
{
    int                     token_output;
    t_output                *tmp_output;

    token_output = check_token((*head)->str);
    *head = (*head)->next;
	tmp_output = ll_new_node_output((*head)->str, token_output);
	ll_lstadd_back_output(&(*tmp)->output, tmp_output);
}
