/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 18:01:40 by msiemons      #+#    #+#                 */
/*   Updated: 2020/11/01 20:24:28 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*strdup_and_free(char **str)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(*str);
	free(*str);
	*str = NULL;
	return (tmp);
}

void			free_env(t_env *envb)
{
	t_env		*tmp;

	while (envb)
	{
		tmp = (envb)->next;
		free(envb->name);
		envb->name = NULL;
		free(envb->value);
		envb->value = NULL;
		free(envb);
		envb = tmp;
	}
	envb = NULL;
}

void			free_array(char **array)
{
	int			y;

	y = 0;
	while (array[y])
	{
		free(array[y]);
		array[y] = NULL;
		y++;
	}
	if (array)
	{
		free(array);
		array = NULL;
	}
}

void			free_list_lexer(t_lexer **sort)
{
	t_lexer		*tmp;

	tmp = NULL;
	while (*sort)
	{
		tmp = (*sort)->next_sort;
		if ((*sort)->str)
		{
			free((*sort)->str);
			(*sort)->str = NULL;
		}
		if ((*sort)->token)
		{
			free((*sort)->token);
			(*sort)->token = NULL;
		}
		free((*sort));
		*sort = tmp;
	}
	*sort = NULL;
}
