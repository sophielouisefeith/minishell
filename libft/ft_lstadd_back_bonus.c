/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back_bonus.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/14 13:06:11 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/21 17:58:42 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list *temp;

	temp = *alst;
	if (*alst == NULL)
		*alst = new;
	else
	{
		while (temp->next)
			temp = temp->next;
		temp->next = new;
	}
}
