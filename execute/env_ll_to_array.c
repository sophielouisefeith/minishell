/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env_ll_to_array.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:21:40 by msiemons      #+#    #+#                 */
/*   Updated: 2020/10/20 16:03:57 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
	int		len_list;
	int		y;

	y = 0;
	len_list = lstsize_env(env);
	array = (char **)malloc(sizeof(char *) * (len_list + 1));
	if (array == NULL)
		malloc_fail(errno = ENOMEM); ///---malloc return???
	while (env)
	{
		array[y] = ft_strjoin(env->name, "=");
		array[y] = ft_strjoin(array[y], env->value);
		y++;
		env = env->next;
	}
	if (array)
		array[len_list] = 0;
	return (array);
}
