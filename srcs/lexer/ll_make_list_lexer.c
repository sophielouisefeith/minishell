/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_make_list_lexer.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 12:12:45 by Maran         #+#    #+#                 */
/*   Updated: 2020/10/30 16:05:57 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer			*ll_new_node_lexer(char *str, int *token)
{
	t_lexer		*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return(NULL);
	new->str = str;
	new->token = token;
	new->next_sort = NULL;
	return (new);
}

void			ll_lstadd_back_lexer(t_lexer **sort, t_lexer *new)
{
	t_lexer		*list;

	list = *sort;
	if (list)
	{
		while (list->next_sort)
			list = list->next_sort;
		list->next_sort = new;
	}
	else
		*sort = new;
}
