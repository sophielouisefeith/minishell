/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   llto2D.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 13:21:40 by msiemons      #+#    #+#                 */
/*   Updated: 2020/08/24 14:10:22 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int  lstsize(t_env *env)
{
	int c;

	c = 0;
	while (env)
	{
		env = env->next;
		c++;
	}
	return (c);
}


int					llto2d(t_env *env)
{
	int	len_list;
	int y;
	char **array;
	
	y = 0;
	len_list = lstsize(env);
	array = (char **)malloc(sizeof(char *) * (len_list + 1));
	if (array == NULL)
		printf("MALLOC FAILED\n");
	while (env)
	{
		array[y] = env->name;
		y++;
		array[y] = env->value;
		y++;
		env = env->next;
	}
	if (array)
		array[len_list] = 0;
	return(array);
}