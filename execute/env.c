/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 10:31:32 by maran         #+#    #+#                 */
/*   Updated: 2020/10/30 15:26:10 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

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
** Subject: env without any options and any arguments.
** 
To do: 
	- waarom zetten we env voorheen eerst terug naar een 2Darray?
	- " env without any options and any arguments", moeten we nog foutmelding als meer dan env gegegevn?
*/

int				env(t_env *_env)
{
	int		ret;

	ret = 0;
	while (_env)
	{
		if (_env->equal)
		{
			ret = write(1, _env->name, ft_strlen(_env->name));
			ret = write(1, "=", 1);
			ret = write(1, _env->value, ft_strlen(_env->value));
			ret = write(1, "\n", 1);
		}
		_env = _env->next;
	}
	return (ret);
}
