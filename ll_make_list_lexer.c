/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_make_list_lexer.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 12:12:45 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/13 10:41:20 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer			*ll_new_node_lexer(char *str, int *token)
{
	t_lexer		*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	// if(!new)
	// 	free_list(*str, NULL);
	// 	error_free(12);
	new->str = str;
	new->token = token;
	new->next = NULL;
	return (new);
}

/*
** if (list): check if there is already an existing node/list
** 		loop to the back of the list. And set last node->next to the new node
**	No list yet. Set head to the new node.
** We have to make a copy of **head, to not change where the initial head is pointing to: the first node of the list.
*/

void			ll_lstadd_back_lexer(t_lexer **sort, t_lexer *new)
{
	t_lexer		*list;

	list = *sort;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*sort = new;
}
