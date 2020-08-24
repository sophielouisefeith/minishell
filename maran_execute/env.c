/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 10:31:32 by maran         #+#    #+#                 */
/*   Updated: 2020/08/24 15:32:20 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

int				main(int argc, char **array)
{
	int		y;

	y = 0;
	while (array)
	{
		write(1, array[y], ft_strlen(array[y]));
		write(1, "=", 1);
		y++;
		write(1, array[y], ft_strlen(array[y]));
		write(1, "\n", 1);
		y++;
	}
}
