/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 14:20:02 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 15:53:58 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "string.h"

static int		check_format(char *str)
{
	int i;

	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (-1);
	i = 1;
	while ((ft_isalnum(str[i]) || str[i] == '_') && str)
		i++;
	if ((!ft_isalnum(str[i]) || str[i] != '_') && str[i] != '\0')
		return (-1);
	return (0);
}

static void		print_declare_x_env(t_env **_env)
{
	t_env	*list;
	t_env	*alpha_env;

	alpha_env = *_env;
	alpha_env_list(alpha_env);
	list = alpha_env;
	while (list)
	{
		write(1, "declare-x ", 10);
		write(1, list->name, ft_strlen(list->name));
		if (list->equal)
		{
			write(1, "=", 1);
			write(1, "\"", 1);
			if (list->value)
				write(1, list->value, ft_strlen(list->value));
			write(1, "\"", 1);
		}
		write(1, "\n", 1);
		list = list->next;
	}
}

static int		not_present_in_env(char **array, t_env **_env, int equal)
{
	t_env	*tmp;

	tmp = ll_new_node_env(ft_strdup(array[0]), ft_strdup(array[1]), equal);
	ll_lstadd_back_env(_env, tmp);
	return (0);
}

static int		check_present_in_env(char **array, t_env **_env, int equal)
{
	t_env	*list;

	list = *_env;
	while (list)
	{
		if (!ft_strcmp(array[0], list->name))
		{
			if (equal)
			{
				list->equal = 1;
				if (!array[1])
					list->value = "";
				else if (ft_strcmp(array[1], list->value))
				{
					free(list->value);
					list->value = ft_strdup(array[1]);
				}
			}
			return (0);
		}
		list = list->next;
	}
	not_present_in_env(array, _env, equal);
	return (0);
}

int				execute_export(t_env **_env, t_command **command)
{
	char	**array;
	int		equal;
	int		ret;
	int		i;

	equal = 0;
	i = 0;
	if (!(*command)->array)
	{
		print_declare_x_env(_env);
		return (0);
	}
	if (ft_strrchr((*command)->array[0], '='))
		equal = 1;
	while ((*command)->array[i] && (*command)->array[i] != '\0')
	{
		array = ft_split2((*command)->array[i], '=');
		ret = check_format(array[0]);
		if (ret == -1)
			return (execute_fail(*command, array));
		check_present_in_env(array, _env, equal);
		free_array(array);
		i++;
	}
	return (0);
}
