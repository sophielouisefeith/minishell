/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_unset.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/29 16:22:20 by maran         #+#    #+#                 */
/*   Updated: 2020/08/26 18:14:45 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** TO DO:
	- Als export klaar is deze ook toevoegen!
*/

/*
** Function receives current node and has to delete the next node.
** current's->next has to be relinked.
**      ___________     __________________      _______________________
** -->|current-node|-->|to be deleted-node|-->|to be currents-next-node|
**     ------------     ------------------      -----------------------
**      ___________     ________________________
** -->|current-node|-->|to be currents-next-node|
**     ------------     ------------------------
*/

static void		ll_remove_next_node(t_env *list)
{
	t_env *tmp;

	if (!list)
		return ;
	tmp = list->next;
	list->next = list->next->next;
	free (tmp->name);
	free (tmp->value);
	free (tmp);
	tmp = NULL;
}

static int		compare_first_node(t_env **_env, char *array_str)
{
	t_env   *tmp;

	tmp = *_env;
	if (!ft_strcmp((*_env)->name, array_str))
	{
		(*_env) = (*_env)->next;
		free (tmp);
		free (tmp->name);
		free (tmp->value);
		return (1);
	}
	return (0);
}

static int		compare_after_first_node(t_env **_env, char *array_str)
{
	t_env	*tmp;

	tmp = *_env;
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

/*
** Part1: Check if there is a match in the first node of env.
** 		If so, set env to the next node and free first node.
** Part2: If there is no match in the first node, check the following nodes.
**		Evertime check if the next node, not the current, is a match. Because
** 		the current node has to be relinked if the next will be deleted
**		(singly linked list).
*/

void			execute_unset(t_command *command, t_env **_env)
{
	int		first_node;
	int		y;

	y = 0;
    if (!command->array)
		return ;
	while (command->array[y])
	{
		first_node = 0;
		first_node = compare_first_node(_env, command->array[y]);
		if (!first_node)
			compare_after_first_node(_env, command->array[y]);
		y++;
	}
}
