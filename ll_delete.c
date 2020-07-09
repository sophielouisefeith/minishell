/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_delete.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 15:49:28 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/09 15:59:07 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void			ll_lstdelone(t_parse *lst)
{
	if (!lst)
		return ;
	lst->str = NULL;
	free(lst);
	lst = NULL;
}

void			ll_lstclear(t_parse **lst)
{
	t_parse *tmp;

	if (!lst)
		return ;
	while (*lst)
	{
		tmp = *lst;
		*lst = (*lst)->next;
		ll_lstdelone(tmp);
	}
	*lst = NULL;
}