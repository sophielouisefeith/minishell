/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specials.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 17:40:26 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 20:35:35 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** In dubbel quotes:
**	- Outer dubbel quotes have te be complete (checked in lexer)
** 	- Inner single quotes are considered as text, don't have to be complete.
*/

static char		*treat_double_quote(char *str, int *i, t_env *envb, int *flag)
{
	int			dollar;
	int			start;
	int			end;
	char		*tmp;

	start = *i;
	dollar = 0;
	if (str[*i - 1] == '$')
		dollar = 1;
	tmp = strdup_and_free(&str);
	str = check_backslash_and_dollar(tmp, i, envb);
	end = *i;
	tmp = strdup_and_free(&str);
	str = delete_double_quotes(tmp, start, end);
	*i = end - 2;
	*flag = 1;
	if (dollar == 1)
	{
		tmp = strdup_and_free(&str);
		str = ft_substr(tmp, 1, ft_strlen(tmp));
		free(tmp);
	}
	return (str);
}

static char		*treat_single_quote(char *str, int *i, int *flag)
{
	int			end;
	int			dollar;
	char		*tmp;

	if (str[*i - 1] == '$')
		dollar = 1;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	end = *i;
	tmp = strdup_and_free(&str);
	str = delete_quotes(tmp, '\'');
	*i = end - 2;
	*flag = 1;
	if (dollar == 1)
	{
		tmp = strdup_and_free(&str);
		str = ft_substr(tmp, 1, ft_strlen(tmp));
		free(tmp);
	}
	return (str);
}

static void		if_no_quote(t_command **command, t_env *envb, int y, int *i)
{
	char		*tmp;

	if ((*command)->array[y][*i] == '\\')
	{
		tmp = strdup_and_free(&(*command)->array[y]);
		(*command)->array[y] = delete_escape_char(tmp, *i);
		(*i)++;
	}
	if ((*command)->array[y][*i] == '$' &&
			(*command)->array[y][*i + 1] == '\\')
	{
		tmp = strdup_and_free(&(*command)->array[y]);
		(*command)->array[y] = delete_escape_char(tmp, (*i + 1));
		(*i)++;
	}
	if ((*command)->array[y][*i] == '$')
	{
		tmp = strdup_and_free(&(*command)->array[y]);
		(*command)->array[y] = if_dollar(tmp, i, envb, 0);
		check_builtin_again(command, envb, y);
	}
}

static void		check_if_quotes(char **str, int *flag, int *i, t_env *envb)
{
	char		*tmp;

	if (is_single_quote((*str)[*i]) && !(*flag))
	{
		tmp = strdup_and_free(str);
		*str = treat_single_quote(tmp, i, flag);
	}
	if (is_double_quote((*str)[*i]) && !(*flag))
	{
		tmp = strdup_and_free(str);
		*str = treat_double_quote(tmp, i, envb, flag);
	}
	return ;
}

void			check_specials(t_command **command, t_env *envb)
{
	int			y;
	int			i;
	int			flag;

	y = 0;
	while ((*command)->array && (*command)->array[y])
	{
		i = 0;
		while ((*command)->array && (*command)->array[y] &&
			(*command)->array[y][i])
		{
			flag = 0;
			check_if_quotes(&(*command)->array[y], &flag, &i, envb);
			if (!is_single_quote((*command)->array[y][i]) &&
				!is_double_quote((*command)->array[y][i]) && !flag)
				if_no_quote(command, envb, y, &i);
			if ((*command)->array[y] == NULL)
			{
				parameter_not_exist(command, &y);
				break ;
			}
			i++;
		}
		y++;
	}
}
