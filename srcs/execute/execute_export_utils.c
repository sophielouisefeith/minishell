/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 15:29:51 by sfeith        #+#    #+#                 */
/*   Updated: 2020/11/01 17:10:08 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				execute_fail(t_command *command, char **array)
{
	free_array(array);
	return (error(command));
}

void			swap(char **s1, char **s2)
{
	char *tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;
}

void			swap_int(int *s1, int *s2)
{
	int tmp;

	tmp = *s2;
	*s2 = *s1;
	*s1 = tmp;
}

void			alpha_env_list(t_env *alpha_env)
{
	t_env		*list1;
	t_env		*list2;
	int			compare;

	list1 = alpha_env;
	while (list1 && list1->next)
	{
		list2 = list1->next;
		while (list2)
		{
			compare = ft_strcmp(list1->name, list2->name);
			if (compare > 0)
			{
				swap(&list1->name, &list2->name);
				swap(&list1->value, &list2->value);
				swap_int(&list1->equal, &list2->equal);
			}
			list2 = list2->next;
		}
		list1 = list1->next;
	}
}

int				check_for_other_parameters(char **array, int y)
{
	if (y > 0)
	{
		if (!array[y + 1] && !array[y - 1])
			return (1);
	}
	else
	{
		if (!array[y + 1])
			return (1);
	}
	return (0);
}
