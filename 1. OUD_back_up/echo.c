/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 15:32:46 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/13 20:29:42 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** To do:
** - return >0 als echo fout.
** - write functie protecten?
** - redirections pas later
*/		

static void			write_echo(t_parse *list)
{
	int 	space;

	space = 0;
	while (list)
	{
		if (space != 0)
			write(1, " ", 1);
		write(1, list->str, ft_strlen(list->str));
		list = list->next;
		space++;
	}
}

int					echo(t_parse **head)
{
	int 		flag_n;
	t_parse		*list;
	// int			flag_redirection;
	// char 		*file_name;

	list = *head;

	flag_n = 0;
	// flag_redirection = 0;
	if (list->next)
		list = list->next;
	else
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strcmp(list->str, "-n"))
	{
		flag_n = 1;
		list = list->next;
	}
	// flag_redirection = check_redirection(list, &file_name);
	// if (flag_redirection)
    // 	redirection(list, flag_redirection, flag_n, file_name);
	// else
	// {
		write_echo(list);
		if (!flag_n)
			write(1, "\n", 1);
	// }
	return (0);
}
