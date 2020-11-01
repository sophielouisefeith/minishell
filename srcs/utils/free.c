/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 16:34:52 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/11/01 12:13:15 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*strdup_and_free(char **str)
{
	char	*tmp;

	tmp = NULL;
	tmp = ft_strdup(*str);
	free (*str);
	*str = NULL;
	return (tmp);
}

void			free_env(t_env *_env)
{
	t_env		*tmp;

	while (_env)
	{
		tmp = (_env)->next;
		free(_env->name);
		_env->name = NULL;
		free(_env->value);
		_env->value = NULL;
		free(_env);
		_env = tmp;
	}
	_env = NULL;
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
