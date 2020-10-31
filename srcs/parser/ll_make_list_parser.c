/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_make_list_parser.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/13 10:17:35 by maran         #+#    #+#                 */
/*   Updated: 2020/10/31 21:10:22 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command		*ll_new_node_command(int num_nodes, int builtin)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	if (num_nodes > 0)
	{
		new->array = (char **)malloc((num_nodes + 1) * sizeof(char *));
		if (!new)
			return (NULL);
	}
	else
		new->array = NULL;
	new->builtin = builtin;
	new->output = NULL;
	new->input = NULL;
	new->pipe_before = 0;
	new->pipe_after = 0;
	new->sem = 0;
	new->next_command = NULL;
	return (new);
}

void			ll_lstadd_back_command(t_command **command, t_command *new)
{
	t_command	*list;

	list = *command;
	if (list)
	{
		while (list->next_command)
			list = list->next_command;
		list->next_command = new;
	}
	else
		*command = new;
}
