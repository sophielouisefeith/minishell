/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 15:09:52 by maran         #+#    #+#                 */
/*   Updated: 2020/09/02 11:57:17 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

/*
** TO DO:
	- Proberen of "while ((*command)->array && (*command)->array[y])" combi ook bij parser werkt, ipv if next bestaat.
	- echo $USER\			--> Merel laat \ weg en print de rest
	- echo $USER|			--> Merel doet niks, gewoon nieuwe prompt
	- Moeten we dit nog verplaatsen naar lexer/parser?
	- Testen: Export expand hij ook name en value
	- Functies te lang.
*/

/*
** When the given parameter (ex. $POEP) doesn't exist in _env:
** check if there a more parameters coming, if so delete the non_existing one
** and move the others in the array. If there are no other parameters,
** the non_existing one will be deleted and the whole 2D array also.
** TO DO:
	- LET OP BIJ FREEEN, gaat dit dan goed?
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

static char 	*check_for_more_expansion(char *new_str2, t_env *_env)
{
	int		i;

	i = 0;
	while (new_str2[i])
	{
		if (new_str2[i] == '$')
			new_str2 = expand(new_str2, i, _env);
		i++;
	}
	return (new_str2);
}

/*
** parameter --> $parameter
** new_str1	-->	 string before $parameter
** new_str2 -->  string after $parameter
**
** 1. i > 0 means the $ sign is not on the first element of the string.
** Therefore everything before $ should be saved in a string.
** 2. Check if there are more special characters after $
** (not alphanumeric and printable, except '_'). Because special chars would
** mean a new string, aphanummeric or '_' would be considered part of the
** $parameter.
** Also check for immediate end of line after $.
** 3. ret == -1 --> Immediate end of line meaning that $ sign should be printed
**    ret == 0  --> no special chars found, so no string after the $parameter 
**    ret > 0   --> special char found, so new_str after $parameter, save in 
**		new_str2. Ret is position of special char.
** 4. If there is a new_str2 (ret > 0) check if special char is a $. If so this
** one should be expanded as wel (recursive).
** 5. If not immediate end of line, search for parameter in _env.
** 6. Join the 3 possible strings, and return this new value.
*/

char			*expand(char *str, int i, t_env *_env)
{
	char	*new_str1;
	char	*new_str2;
	char	*parameter;
	int		ret;

	new_str1 = NULL;
	parameter = NULL;
	new_str2 = NULL;
	if (i > 0)
		new_str1 = ft_substr(str, 0, i);
	ret = is_special_char(str, (i + 1));
	if (ret == -1)
		parameter = "$";
	if (ret == 0)
		parameter = ft_substr(str, (i + 1), ft_strlen(str));
	if (ret > 0)
	{
		parameter = ft_substr(str, (i + 1), (ret - i - 1)) ;
		new_str2 = ft_substr(str, ret, ft_strlen(str));
		new_str2 = check_for_more_expansion(new_str2, _env);
	}
	if (ret != -1)
		parameter = search_node(_env, parameter);
	parameter = join_strings(new_str1, parameter, new_str2);
	return (parameter);
}

/*
** ($?) Expands to the exit status of the most recently executed foreground pipeline.
** Single quote cases will not be expanded.
** Break out of first while loop when handled $. Optional other $ in
** the array[y] are already handled.
*/

static void		if_dollar(t_command **command, t_env *_env, int *y, int i)
{
	char	*value;

	if (!ft_strcmp("$?", (*command)->array[*y]))
		value = ft_itoa((*command)->exit_status);
	else
		value = expand((*command)->array[*y], i, _env);
	if (value == NULL)
		parameter_not_exist(command, y);
	else
		(*command)->array[*y] = value;
}

void			parameter_expansion(t_command **command, t_env *_env)
{
	int		y;
	int		i;

	y = 0;
	while ((*command)->array && (*command)->array[y])
	{
		i = 0;
		while((*command)->array[y][i])
		{
			if ((*command)->array[y][i] == '$' && (*command)->quote[y] != token_quote)
			{
				if_dollar(command, _env, &y, i);
				break ;
			}
			i++;
		}
		y++;
	}
}
