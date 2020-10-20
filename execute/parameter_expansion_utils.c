/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion_utils.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:54:16 by msiemons      #+#    #+#                 */
/*   Updated: 2020/10/19 16:56:46 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

# include "../minishell.h"

/*
** TO DO:
		- is_special_char die buiten parameter_exp wordt gebruikt. Kan die ook dollar_is_speci...
		gebruiken? Verschil zit in check of er een getal zit op de eerste plek.
*/

/*
** Search_node also used by execute_cd
*/

char			*search_node(t_env *_env, char *search)
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
	int		save_i;

	save_i = i;
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (ft_isprint(str[i]) && !ft_isalnum(str[i]) && str[i] != '_')
			return (i);
		i++;

	}
	return (0);
}

/*
** Check if there is non-alphanummeric character.
** '_' will be counted as a alphanummeric)
** Return position of non-alphanummeric character. If non return 0.
** Numbers can be in _env, but not on the first position.
** So if there is number on the first postion, return > 0.
*/

int				dollar_is_special_char(char *str, int i)
{
	int		save_i;

	save_i = i;
	if (!str[i])
		return (-1);
	while (str[i])
	{
		if (ft_isprint(str[i]) && !ft_isalnum(str[i]) && str[i] != '_')	
			return (i);
		if (ft_isdigit(str[i]) && i == save_i)
			return (i);
		i++;
	}
	return (0);
}

void			initiate_dollar(t_dollar *dollar, int quote)
{
	dollar->new_str1 = NULL;
	dollar->parameter = NULL;
	dollar->new_str2 = NULL;
	dollar->flag_group2 = 0;
	dollar->flag_qm = 0;
	dollar->quote = quote;
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
	char	*joined;

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
