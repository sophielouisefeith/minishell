/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 12:04:26 by maran         #+#    #+#                 */
/*   Updated: 2020/08/20 13:25:48 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "../minishell.h"


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
/*
** gcc echo.c ../ft_strcmp.c ../libft/ft_strlen.c -o echo
*/

int					main(int argc, char **array)
{
	int 		flag_n;
	int 		y;
	// t_command	*list;

	// list = head_command;
    // printf("IN ECHO\n");
	// printf("array[0] = [%s]\n", array[0]);
	// printf("arrray[1] = [%s]\n", array[1]);
	flag_n = 0;
	y = 0;
	// if (array[0])
	// {
	// 	write(1, "\n", 1);
	// 	return (0);
	// }
	// if (!ft_strcmp(array[0], "-n"))
	// {
	// 	flag_n = 1;
	// 	y++;
	// }
	write_echo(array, y);
	if (!flag_n)
		write(1, "\n", 1);
	return (0);    
}