/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 10:31:32 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 17:56:38 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
