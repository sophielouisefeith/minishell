/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_ll_to_array.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:21:40 by msiemons      #+#    #+#                 */
/*   Updated: 2020/11/01 19:52:07 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		lstsize_env(t_env *env)
{
	int		c;

	c = 0;
	while (env)
	{
		env = env->next;
		c++;
	}
	return (c);
}

char			**env_ll_to_array(t_env *env)
{
	char	**array;
	char	*tmp;
	int		len_list;
	int		y;

	y = 0;
	len_list = lstsize_env(env);
	array = (char **)malloc(sizeof(char *) * (len_list + 1));
	if (array == NULL)
	{
		errno = ENOMEM;
		malloc_fail();
	}
	while (env)
	{
		tmp = ft_strjoin(env->name, "=");
		array[y] = ft_strjoin(tmp, env->value);
		free(tmp);
		tmp = NULL;
		y++;
		env = env->next;
	}
	if (array)
		array[len_list] = 0;
	return (array);
}
