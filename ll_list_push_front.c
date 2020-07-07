/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_list_push_front.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 12:12:45 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/07 14:00:35 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parse	*ll_new_node(void *content)
{
	t_parse	*new;

	new = malloc(sizeof(t_list));
	if (!new)
		return (0);
	new->str = content;
	new->next = NULL;
	return (new);
}

void		ll_list_push_front(t_parse **begin_list, void *data)
{
	t_parse		*tmp;

	if (begin_list == NULL)
		*begin_list = ll_new_node(data);
	else
	{
		tmp = ll_new_node(data);
		tmp->next = *begin_list;
		*begin_list = tmp;
	}
}
