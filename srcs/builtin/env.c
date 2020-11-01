/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 10:31:32 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 20:28:14 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				env(t_env *envb)
{
	int		ret;

	ret = 0;
	while (envb)
	{
		if (envb->equal)
		{
			ret = write(1, envb->name, ft_strlen(envb->name));
			ret = write(1, "=", 1);
			ret = write(1, envb->value, ft_strlen(envb->value));
			ret = write(1, "\n", 1);
		}
		envb = envb->next;
	}
	return (ret);
}
