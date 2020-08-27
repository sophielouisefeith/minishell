/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 15:09:52 by maran         #+#    #+#                 */
/*   Updated: 2020/08/27 22:04:41 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

/*
** ($?) Expands to the exit status of the most recently executed foreground pipeline.
** Echo doesn't let through single quote cases. Theses shouldn't be expanded.
**TO DO:
	-strtrim trimt van 2 kanten gaat dat wel goed?
	- Moeten we ook braces?
	- Andere plek expanden, ook nodig voor cd en export
	- Export expand hij ook name en value
*/

static char		*search_node(t_env *_env, char *search)
{
	while (_env)
	{
		if (!ft_strcmp(search, _env->name))
			return (_env->value);
		_env = _env->next;
	}
	return (NULL);
}

char		*parameter_expansion(t_command *command, t_env *_env, int y)
{
	char *new_str;
	char *value;
	
	if (!ft_strcmp("$?", command->array[y]))
		return (ft_itoa(command->exit_status));
	else
	{
		new_str = ft_strtrim(command->array[y], "$");
		value = search_node(_env, new_str);
	}
	if (value == NULL)
		return ("");
	return (value);
}