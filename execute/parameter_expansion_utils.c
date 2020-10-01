/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion_utils.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:54:16 by msiemons      #+#    #+#                 */
/*   Updated: 2020/10/01 22:03:11 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

/*
** Search_node also used by execute_cd
*/

char		*search_node(t_env *_env, char *search)
{
	while (_env)
	{
		if (!ft_strcmp(search, _env->name))
			return (_env->value);
		_env = _env->next;
	}
	return (NULL);
}

int				is_special_char(char *str, int i)
{
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (ft_isprint(str[i]) && !ft_isalnum(str[i]) && str[i] != '_') //&& str[i] != '\"') //new "
			return (i);
		i++;

	}
	return (0);
}

/*
**	new_str1	parameter	new_str2
**	0			0			0
**	1			1			1
**	1			0			0
**	1			1			0
**	1			0			1
**	0			1			0
**	0			1			1
**	0			0			1
*/
 
char			*join_strings(char *new_str1, char *parameter, char *new_str2)
{
	char 	*joined;

	if (!new_str1 && !parameter && !new_str2)
		return (NULL);
	if (new_str1 && parameter && new_str2)
	{
		joined = ft_strjoin(new_str1, parameter);
		joined = ft_strjoin(joined, new_str2);
	}
	if (new_str1 && !parameter && !new_str2)
		joined = new_str1;
	if (new_str1 && parameter && !new_str2)
		joined = ft_strjoin(new_str1, parameter);
	if (new_str1 && !parameter && new_str2)
		joined = ft_strjoin(new_str1, new_str2);
	if (!new_str1 && parameter && !new_str2)
		joined = parameter;
	if (!new_str1 && parameter && new_str2)
		joined = ft_strjoin(parameter, new_str2);
	if (!new_str1 && !parameter && new_str2)
		joined = new_str2;
	return (joined);
}
