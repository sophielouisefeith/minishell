/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 15:32:46 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/30 14:25:03 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** To do:
** - return >0 als echo fout.
** - write functie protecten?
** - redirections pas later
*/		

static void			write_echo(char **array, int y)
{
	int 	space;

	space = 0;
	while (array[y])
	{
		if (space != 0)
			write(1, " ", 1);
		write(1, array[y], ft_strlen(array[y]));
		y++;
		space++;
	}
}

int					execute_echo(t_command *head_command)
{
	int 		flag_n;
	int 		y;
	t_command	*list;

	list = head_command;
	flag_n = 0;
	y = 0;
	if (list->array[0])
	{
		write(1, "\n", 1);
		return (0);
	}
	if (!ft_strcmp(list->array[0], "-n"))
	{
		flag_n = 1;
		y++;
	}
	write_echo(list->array, y);
	if (!flag_n)
		write(1, "\n", 1);
	return (0);
}
