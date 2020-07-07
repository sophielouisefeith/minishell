/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_add_back.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 12:12:45 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/07 19:24:50 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_parse	*ll_new_node(void *content)
{
	t_parse		*new;

	new = (t_parse *)malloc(sizeof(t_parse));
	if (!new)
		return (0);
	new->str = content;
	new->next = NULL;
	return (new);
}

// void			ll_list_push_front(t_parse **begin_list, void *data)
// {
// 	t_parse		*tmp;

// 	if (begin_list == NULL)
// 		*begin_list = ll_new_node(data);
// 	else
// 	{
// 		tmp = ll_new_node(data);
// 		tmp->next = *begin_list;
// 		*begin_list = tmp;
// 	}
// }

static void	ft_lstadd_front1(t_parse **alst, t_parse *new)
{
	new->next = *alst;
	*alst = new;
}

void		ft_lstadd_back1(t_parse **alst, t_parse *new)
{
	t_parse	*list;

	list = *alst;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		ft_lstadd_front1(alst, new);
}
