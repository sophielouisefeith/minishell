/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_make_list.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 12:12:45 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/15 23:35:55 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse			*ll_new_node(void *content)
{
	t_parse		*new;

	new = (t_parse *)malloc(sizeof(t_parse));
	if (!new)
		return (0);
	new->str = content;
	new->next = NULL;
	return (new);
}


static void		ll_lstadd_front(t_parse **head, t_parse *new)
{
	
	// new->next = *head; 			//is dit niet overbodig?
	*head = new;
}

/*
** if (list): check if there is already an existing node/list
** 		loop to the back of the list. And set last node->next to the new node
**	No list yet. Set head to the new node.
** We have to make a copy of **head, to not change where the initial head is pointing to: the first node of the list.
*/

void			ll_lstadd_back(t_parse **head, t_parse *new)
{
	t_parse		*list;

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
