/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 09:38:34 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/11 10:15:16 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_input		*ll_new_node_input(char *str_input)
{
	t_input		*new;

	new = (t_input *)malloc(sizeof(t_input));
	if (!new)
		error_free(errno);
	new->str_input = str_input;
	new->next = NULL;
	return (new);
}

static void			ll_lstadd_back_input(t_input **input, t_input *new)
{
	t_input		*list_input;

	list_input = *input;
	if (list_input)
	{
		while (list_input->next)
			list_input = list_input->next;
		list_input->next = new;
	}
	else
		*input = new;
}

void				input_fill(t_lexer **sort, t_command **tmp)
{
    t_input		*tmp_input;

    *sort = (*sort)->next;
    tmp_input = ll_new_node_input((*sort)->str);
	ll_lstadd_back_input(&(*tmp)->input, tmp_input);
}
