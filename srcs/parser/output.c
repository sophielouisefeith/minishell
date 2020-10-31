/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 09:30:21 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/10/31 21:30:02 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_output		*ll_new_node_output(char *str_output, int token)
{
	t_output	*new;

	new = (t_output *)malloc(sizeof(t_output));
	if (!new)
		return (NULL);
	new->str_output = str_output;
	new->token = token;
	new->next_output = NULL;
	return (new);
}

static void			ll_lstadd_back_output(t_output **output, t_output *new)
{
	t_output	*list_output;

	list_output = *output;
	if (list_output)
	{
		while (list_output->next_output)
			list_output = list_output->next_output;
		list_output->next_output = new;
	}
	else
		*output = new;
}

void				output_fill(t_lexer **sort, t_command **tmp, int token)
{
	t_output	*tmp_output;
	char		*str;

	*sort = (*sort)->next_sort;
	str = ft_strdup((*sort)->str);
	if (str == NULL)
		malloc_fail();
	tmp_output = ll_new_node_output(str, token);
	if (tmp_output == NULL)
		malloc_fail();
	ll_lstadd_back_output(&(*tmp)->output, tmp_output);
}
