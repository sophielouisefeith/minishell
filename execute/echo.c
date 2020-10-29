/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:30 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/28 18:14:07 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>
#include "../minishell.h"

static int		write_echo(char **array, int y)
{
	int		space;
	int 	ret;

	ret = 0;
	space = 0;
	while (array[y])
	{
		if (space != 0)
			ret = write(1, " ", 1);
		ret = write(1, array[y], ft_strlen(array[y]));
		y++;
		space++;		
	}
	return (ret);
}

int				echo(char **array)
{
	int		flag_n;
	int		ret;
	int		y;

	flag_n = 0;
	ret = 0;
	y = 0;
	if (array == NULL)
	{
		ret = write(1, "\n", 1);
		return (ret);
	}							//new
	if (!ft_strcmp(array[0], "-n"))
	{
		flag_n = 1;
		y++;
	}
	ret = write_echo(array, y);
	if (!flag_n)
		ret = write(1, "\n", 1);
	return (ret);
}