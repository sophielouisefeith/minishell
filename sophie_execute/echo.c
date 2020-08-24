/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:30 by sfeith        #+#    #+#                 */
/*   Updated: 2020/08/24 14:14:10 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../minishell.h"

/*
** gcc echo.c ../ft_strcmp.c ../libft/ft_strlen.c -o echo
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

int					main(int argc, char **array)
{
	int 		flag_n;
	int 		y;

	flag_n = 0;
	y = 0;
	if (!ft_strcmp(array[0], "-n"))
	{
		flag_n = 1;
		y++;
	}
	write_echo(array, y);
	if (!flag_n)
		write(1, "\n", 1);
	return (0);    
}