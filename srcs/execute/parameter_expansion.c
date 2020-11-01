/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parameter_expansion.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/27 15:09:52 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 17:45:06 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			parameter_not_exist(t_command **command, int *y)
{
	int			new_y;

	if (check_for_other_parameters((*command)->array, *y))
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

static int		group_and_start_newstr2(char *str, int ret, int i, int *start)
{
	int			group;

	if (str[ret - 1] == '$')
	{
		if (str[ret] == '\"' || str[ret] == '\'' || str[ret] == '\\')
			group = 0;
		if ((str[ret] >= '0' && str[ret] <= '9') || str[ret] == '*'
			|| str[ret] == '@' || str[ret] == '!' || str[ret] == '&'
			|| str[ret] == '$' || str[ret] == '#'
			|| str[ret] == '-')
			group = 1;
		if (str[ret] == '%' || str[ret] == '^' || str[ret] == '+' ||
			str[ret] == ',' || str[ret] == '.' || str[ret] == '/' ||
			str[ret] == ':' || str[ret] == '=' || str[ret] == ']' ||
			str[ret] == '}' || str[ret] == '~')
			group = 2;
		if (str[ret] == '?')
			group = 4;
	}
	else
		group = 5;
	*start = (group == 1 || group == 4) ? (ret + 1) : ret;
	*start = (group == 2) ? i : (*start);
	return (group);
}

static void		special_char_found(t_dollar **dollar, char *str, int i)
{
	int		group;
	int		start;

	group = group_and_start_newstr2(str, (*dollar)->ret, i, &start);
	if (group == 0 && (*dollar)->quote)
	{
		(*dollar)->flag_group2 = 1;
		(*dollar)->ret = -1;
		(*dollar)->parameter = ft_strdup("$");
	}
	if (group == 2)
		(*dollar)->flag_group2 = 1;
	if (group == 4)
	{
		(*dollar)->flag_qm = 1;
		(*dollar)->parameter = ft_itoa(g_exit_status);
	}
	if (group == 5)
		(*dollar)->parameter = ft_substr(str, (i + 1),
			((*dollar)->ret - i - 1));
	(*dollar)->new_str2 = ft_substr(str, start, ft_strlen(str));
}

static char		*ret_parammeter(char *str, t_dollar *dollar)
{
	free(str);
	str = NULL;
	str = join_strings(dollar->new_str1, dollar->parameter,
		dollar->new_str2);
	free_if_dollar(&dollar);
	return (str);
}

char			*if_dollar(char *str, int *i, t_env *_env, int quote)
{
	t_dollar	*dollar;
	char		*tmp;

	dollar = (t_dollar *)malloc(sizeof(t_dollar));
	initiate_dollar(dollar, quote);
	if (*i > 0)
		dollar->new_str1 = ft_substr(str, 0, *i);
	dollar->ret = dollar_is_special_char(str, (*i + 1));
	if (dollar->ret == -1)
		dollar->parameter = ft_strdup("$");
	if (dollar->ret == 0)
		dollar->parameter = ft_substr(str, (*i + 1), ft_strlen(str));
	if (dollar->ret > 0)
		special_char_found(&dollar, str, *i);
	if (dollar->ret != -1 && dollar->parameter && !dollar->flag_qm)
	{
		tmp = ft_strdup(dollar->parameter);
		free(dollar->parameter);
		dollar->parameter = NULL;
		dollar->parameter = search_node(_env, tmp);
	}
	if (dollar->new_str2 && !dollar->flag_group2 && (dollar->new_str2[0] == '$'
		|| dollar->new_str2[0] == '\'' || dollar->new_str2[0] == '\"'))
		(*i)--;
	return (ret_parammeter(str, dollar));
}
