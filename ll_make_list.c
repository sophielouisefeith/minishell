/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_make_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 12:12:45 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/20 12:38:02 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_lexer			*ll_new_node(void *content, int type)
{
	t_lexer		*new;

	new = (t_lexer *)malloc(sizeof(t_lexer));
	if (!new)
		return (0);
	new->str = content;
	new->type = type;
	new->next = NULL;
	return (new);
}

/*
** if (list): check if there is already an existing node/list
** 		loop to the back of the list. And set last node->next to the new node
**	No list yet. Set head to the new node.
** We have to make a copy of **head, to not change where the initial head is pointing to: the first node of the list.
*/

void			ll_lstadd_back(t_lexer **head, t_lexer *new)
{
	t_lexer		*list;

	list = *head;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*head = new;
}