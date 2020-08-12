/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 09:30:21 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/12 17:36:55 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_output		*ll_new_node_output(char *str_output, int token)
{
	t_output	*new;

	new = (t_output *)malloc(sizeof(t_output));
	// if (!new)
	// 	error_free(errno);;
	new->str_output = str_output;
	new->token = token;
	new->next = NULL;
	return (new);
}

static void			ll_lstadd_back_output(t_output **output, t_output *new)
{
	t_output	*list_output;

	list_output = *output;
	if (list_output)
	{
		while (list_output->next)
			list_output = list_output->next;
		list_output->next = new;
	}
	else
		*output = new;
}

void				output_fill(t_lexer **sort, t_command **tmp, int token)
{
    t_output	*tmp_output;

    *sort = (*sort)->next;
	tmp_output = ll_new_node_output((*sort)->str, token);
	ll_lstadd_back_output(&(*tmp)->output, tmp_output);
}
