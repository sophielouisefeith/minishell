/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 15:32:46 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/09 15:35:14 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** return >0 als echo fout.
** write functie protecten?
*/		

static void			write_echo(t_parse *head)
{
	int 	space;

	space = 0;
	while (head)
	{
		if (space != 0)
			write(1, " ", 1);
		write(1, head->str, ft_strlen(head->str));
		head = head->next;
		space++;
	}
}

int					echo(t_parse *head)
{
	int 	flag_n;

	flag_n = 0;
	if (head->next)
		head = head->next;
	else
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strcmp(head->str, "-n"))
	{
		flag_n = 1;
		head = head->next;
	}
	write_echo(head);
	if (!flag_n)
		write(1, "\n", 1);
	return (0);
}