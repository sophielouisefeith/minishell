/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   output.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 09:30:21 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/20 15:02:04 by maran         ########   odam.nl         */
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
	char 		*str;

    *sort = (*sort)->next_sort;
	str = ft_strdup((*sort)->str);											//new
	tmp_output = ll_new_node_output(str, token);							//new
	ll_lstadd_back_output(&(*tmp)->output, tmp_output);
}
