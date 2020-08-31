/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 10:31:32 by maran         #+#    #+#                 */
/*   Updated: 2020/08/31 12:00:42 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

// void				env(char **array)
// {
// 	int		y;

// 	y = 0;
// 	while (array[y])
// 	{
// 		write(1, array[y], ft_strlen(array[y]));
// 		write(1, "=", 1);
// 		y++;
// 		write(1, array[y], ft_strlen(array[y]));
// 		write(1, "\n", 1);
// 		y++;
// 	}
// }

/*
** To do: 
	- waarom zetten we env voorheen eerst terug naar een 2Darray?
*/

void				env(t_env *_env)
{
	int		y;

	y = 0;
	while (_env)
	{
		write(1, _env->name, ft_strlen(_env->name));
		if (_env->equal)
			write(1, "=", 1);
		write(1, _env->value, ft_strlen(_env->value));
		write(1, "\n", 1);
		_env = _env->next;
	}
}