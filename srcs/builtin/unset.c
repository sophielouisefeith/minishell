/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   unset.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 16:22:20 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 20:30:28 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ll_remove_next_node(t_env *list)
{
	t_env *tmp;

	if (!list)
		return ;
	tmp = list->next;
	list->next = list->next->next;
	free(tmp->name);
	free(tmp->value);
	free(tmp);
	tmp = NULL;
}

static int		compare_first_node(t_env **envb, char *array_str)
{
	t_env	*tmp;

	tmp = *envb;
	if (!ft_strcmp((*envb)->name, array_str))
	{
		(*envb) = (*envb)->next;
		free(tmp);
		free(tmp->name);
		free(tmp->value);
		return (1);
	}
	return (0);
}

static int		compare_after_first_node(t_env **envb, char *array_str)
{
	t_env	*tmp;

	tmp = *envb;
	while (tmp->next)
	{
		if (!ft_strcmp(tmp->next->name, array_str))
		{
			ll_remove_next_node(tmp);
			return (1);
		}
		tmp = tmp->next;
	}
	return (0);
}

static void		error_unset(t_command *command)
{
	char *str;

	str = command->array[0];
	if (str[0] == '-' && str[1] != 'v' && str[1] != 'f'
		&& str[1] != '\0' && str[1] != '-')
	{
		write(1, "bash: unset: ", 11);
		write(1, str, ft_strlen(str));
		write(1, " invalid option", 15);
		write(1, "\n", 1);
		write(1, "unset: usage: unset [-f] [-v]", 29);
		write(1, "\n", 1);
		g_exit_status = 2;
	}
	else
		return ;
}

int				execute_unset(t_command *command, t_env **envb)
{
	int		first_node;
	int		y;
	int		ret;

	y = 0;
	if (!command->array)
		return (0);
	if (command->array[y])
		error_unset(command);
	if ((!ft_strncmp(command->array[y], "-", ft_strlen(command->array[y]))\
	&& (*command).array[y][1] == '\0') || (*command).array[y][0] == '%')
		error(command);
	while (command->array[y])
	{
		first_node = 0;
		ret = is_special_char(command->array[y], 0);
		if (ret > 0)
			return (-1);
		first_node = compare_first_node(envb, command->array[y]);
		if (!first_node)
			compare_after_first_node(envb, command->array[y]);
		y++;
	}
	return (0);
}
