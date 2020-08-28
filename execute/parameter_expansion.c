/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 15:09:52 by maran         #+#    #+#                 */
/*   Updated: 2020/08/28 12:05:00 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

/*
** ($?) Expands to the exit status of the most recently executed foreground pipeline.
** Single quote cases will not be expanded.
** TO DO:
	- strtrim trimt van 2 kanten gaat dat wel goed?
	- Moeten we ook braces?
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

/*
** When the given parameter (ex. $POEP) doesn't exist in _env:
** check if there a more parameters coming, if so delete the non_existing one
** and move the others in the array. If there are no other parameters,
** the non_existing one will be deleted and the whole 2D array also.
** TO DO:
	LET OP BIJ FREEEN, gaat dit dan goed?
*/

static void		parameter_not_exist(t_command **command, int *y)
{
	int		new_y;

	if (!(*command)->array[*y + 1])
	{
		free((*command)->array[*y]);
		free((*command)->array);
		(*command)->array[*y] = NULL;
		(*command)->array = NULL;
	}
	else
	{
		new_y = *y - 1;
		while ((*command)->array[*y + 1])
		{
			(*command)->array[*y] = (*command)->array[*y + 1];
			(*y)++;
		}
		(*command)->array[*y] = NULL;
		(*y) = new_y;
	}
}

/*
** TO DO:
	- Proberen of "while ((*command)->array && (*command)->array[y])" combi ook bij parser werkt, ipv if next bestaat.
*/

void			parameter_expansion(t_command **command, t_env *_env)
{
	char	*new_str;
	char	*value;
	int		y;

	y = 0;
	while ((*command)->array && (*command)->array[y])
	{
		if ((*command)->array[y][0] == '$' && (*command)->quote[y] != token_quote)
		{
			if (!ft_strcmp("$?", (*command)->array[y]))
				value = ft_itoa((*command)->exit_status);
			else
			{
				new_str = ft_strtrim((*command)->array[y], "$");
				value = search_node(_env, new_str);
			}
			if (value == NULL)
				parameter_not_exist(command, &y);
			else
				(*command)->array[y] = value;
		}
		y++;
	}
}
