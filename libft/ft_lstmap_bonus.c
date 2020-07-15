/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap_bonus.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 15:34:38 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/21 12:31:26 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *newlist;

	if (!lst)
		return (NULL);
	newlist = (malloc(sizeof(t_list)));
	if (!newlist)
	{
		ft_lstclear(&lst, del);
		return (NULL);
	}
	newlist->content = f(lst->content);
	newlist->next = ft_lstmap(lst->next, f, del);
	return (newlist);
}
