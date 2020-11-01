/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion_utils.c                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:54:16 by msiemons      #+#    #+#                 */
/*   Updated: 2020/11/01 20:32:51 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*search_node(t_env *envb, char *search)
{
	while (envb)
	{
		if (!ft_strcmp(search, envb->name))
		{
			free(search);
			return (ft_strdup(envb->value));
		}
		envb = envb->next;
	}
	free(search);
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

char			*join_strings(char *new_str1, char *parameter, char *new_str2)
{
	char	*joined1;
	char	*joined;

	if (!new_str1 && !parameter && !new_str2)
		return (NULL);
	if (new_str1 && parameter && new_str2)
	{
		joined1 = ft_strjoin(new_str1, parameter);
		joined = ft_strjoin(joined1, new_str2);
		free(joined1);
	}
	if (new_str1 && !parameter && !new_str2)
		joined = ft_strdup(new_str1);
	if (new_str1 && parameter && !new_str2)
		joined = ft_strjoin(new_str1, parameter);
	if (new_str1 && !parameter && new_str2)
		joined = ft_strjoin(new_str1, new_str2);
	if (!new_str1 && parameter && !new_str2)
		joined = ft_strdup(parameter);
	if (!new_str1 && parameter && new_str2)
		joined = ft_strjoin(parameter, new_str2);
	if (!new_str1 && !parameter && new_str2)
		joined = ft_strdup(new_str2);
	return (joined);
}
