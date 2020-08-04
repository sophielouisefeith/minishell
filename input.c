/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 09:38:34 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/04 11:11:07 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_input			*ll_new_node_input(void *content, int token_input)
{
	t_input		*new;

	new = (t_input *)malloc(sizeof(t_input));
	if (!new)
		return (0);
	new->str_input = content;
    new->token_input = token_input;
    printf("node---str_input[%s]\n", new->str_input);
    printf("node---token_input[%d]\n", new->token_input);
	new->next_input = NULL;
	return (new);
}

static void			ll_lstadd_back_input(t_input **head_input, t_input *new_input)
{
	t_input		*list_input;

	list_input = *head_input;
	if (list_input)
	{
		while (list_input->next_input)
			list_input = list_input->next_input;
		list_input->next_input = new_input;
	}
	else
		*head_input = new_input;
}

void            input_fill(t_lexer **head)
{
    t_input                 *tmp_input;
    t_input                 input;
    t_input                 *input_head; //head
    int                    token_input;

    input_head = NULL;
    token_input = check_token((*head)->str);
    *head = (*head)->next;
    tmp_input = ll_new_node_input((*head)->str, token_input);
	ll_lstadd_back_input(&input_head, tmp_input);
}
