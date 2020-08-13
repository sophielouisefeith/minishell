/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 15:32:46 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/13 16:29:03 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** To do:
** - return >0 als echo fout.
** - write functie protecten?
** - redirections pas later
*/		

/*
** The orginal. Direct schrijven.
*/

// static void			write_echo(char **array, int y)
// {
// 	int 	space;

// 	space = 0;
// 	while (array[y])
// 	{
// 		if (space != 0)
// 			write(1, " ", 1);
// 		write(1, array[y], ft_strlen(array[y]));
// 		y++;
// 		space++;
// 	}
// }

// int					execute_echo(t_command *head_command)
// {
// 	int 		flag_n;
// 	int 		y;
// 	t_command	*list;

// 	list = head_command;
// 	flag_n = 0;
// 	y = 0;
// 	if (list->array[0])
// 	{
// 		write(1, "\n", 1);
// 		return (0);
// 	}
// 	if (!ft_strcmp(list->array[0], "-n"))
// 	{
// 		flag_n = 1;
// 		y++;
// 	}
// 	write_echo(list->array, y);
// 	if (!flag_n)
// 		write(1, "\n", 1);
// 	return (0);
// }


/*
** Test schrijven naar fd:
*/

static void			write_echo(char **array, int y, char *buf, int *i)
{
	int 	space;
	int		x;

	space = 0;
	while (array[y])
	{
		x = 0;
		if (space != 0)
		{
			buf[*i] = ' ';
			(*i)++;
		}
		while (array[y][x])
		{
			buf[*i] = array[y][x];
			(*i)++;
			x++;
		}
		y++;
		space++;
	}
}

char			*execute_echo(t_command **command)
{
	int 		flag_n;
	int 		y;
	char		*buf;
	int i;

	flag_n = 0;
	y = 0;
	i = 0;
	buf = (char *)malloc(sizeof(char) * 1000);
	
	if (!(*command)->array[0])
	{
		write(buf[i], "\n", 1);
		return (0);
	}
	if (!ft_strcmp((*command)->array[0], "-n"))
	{
		flag_n = 1;
		y++;
	}
	write_echo((*command)->array, y, buf, &i);
	if (!flag_n)
		write(buf[i], "\n", 1);
	return (buf);
}