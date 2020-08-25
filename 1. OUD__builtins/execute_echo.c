/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_echo.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/09 15:32:46 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/24 17:50:01 by sfeith        ########   odam.nl         */
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

static int			length_total_array(char **array, int y)
{
	int 	len;
	
	len = 0;
	while (array[y])
	{
		len = len + ft_strlen(array[y]);
		len++;
		y++;
	}
	return (len);
}

static char			*write_echo(char **array, int y, int *i)
{
	int 	space;
	int		x;
	char 	*buf;

	buf = (char *)malloc(sizeof(char) * length_total_array(array, y));
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
	buf[*i] = '\0';
	return (buf);
}

char			*execute_echo(t_command **command)
{
	char		*buf;
	int 		flag_n;
	int 		i;
	int 		y;

	i = 0;
	y = 0;
	flag_n = 0;
	// if (!(*command)->array[0])
	// {
	// 	write(buf[i], "\n", 1);
	// 	return (0);
	// }
	// if (!ft_strcmp((*command)->array[0], "-n"))
	// {
	// 	flag_n = 1;
	// 	y++;
	// }
	buf = write_echo((*command)->array, y, &i);
	// if (!flag_n)
	// 	write(buf[i], "\n", 1);
	return (buf);
}