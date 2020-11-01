/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specials.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 17:40:26 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 12:52:03 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** TO DO:
	- Single quotes: //Freeen oude malloc?
	!!! - Check_builtin_again:  Misschien in if_dollar zetten. Zo niet ook onder andere if_dollars zetten! (wacht op andere aanpassingen).	
*/

/*
** In dubbel quotes:
**	- Outer dubbel quotes have te be complete (checked in lexer)
** 	- Inner single quotes are considered as text, don't have to be complete.
**  - nog eerst str = NULL 
*/

static char		*treat_double_quote(char *str, int *i, t_env *_env, int *flag)
{
	int		dollar;
	int		start;
	int		end;
	char 	*tmp;

	start = *i;
	dollar = 0;
	if (str[*i - 1] == '$')
		dollar = 1;
	tmp = ft_strdup(str);
	free(str);
	str = check_backslash_and_dollar(tmp, i, _env);
	end = *i;
	tmp = ft_strdup(str);
	free(str);
	str = delete_double_quotes(tmp, start, end);
	*i = end - 2;
	*flag = 1;
	if (dollar == 1)
	{
		tmp = ft_strdup(str);
		free(str);
		str = ft_substr(tmp, 1, ft_strlen(tmp));
		free(tmp);
	}
	return (str);
}

static char		*treat_single_quote(char *str, int *i, int *flag)
{
	int		end;
	int		dollar;
	char	*tmp;

	if (str[*i - 1] == '$')
		dollar = 1;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	end = *i;
	tmp = ft_strdup(str);
	free(str);
	str = delete_quotes(tmp, '\'');
	*i = end - 2;
	*flag = 1;
	if (dollar == 1)
	{
		tmp = ft_strdup(str);
		free(str);
		str = ft_substr(tmp, 1, ft_strlen(tmp));
		free(tmp);
	}
	return (str);
}

/*
** Check_builtin_again: checks if there are commands in the _env variables ($)
** Ex. export LS="ls -la" 
*/

static void		if_no_quote(t_command **command, t_env *_env, int y, int *i)
{
	char *tmp;

	if ((*command)->array[y][*i] == '\\')
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;
		(*command)->array[y] = delete_escape_char(tmp, *i);				//tmp wordt gefreeeet
		(*i)++; 			// Peeeert test --> UITZETTEN
	}
	if ((*command)->array[y][*i] == '$' &&
			(*command)->array[y][*i + 1] == '\\')
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;
		(*command)->array[y] = delete_escape_char(tmp, (*i + 1));
		(*i)++;
	}
	if ((*command)->array[y][*i] == '$')
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;
		(*command)->array[y]  = if_dollar(tmp, i, _env, 0);
		check_builtin_again(command, _env, y);
	}
}

static void		check_if_quotes(t_command **command, int *flag, int y, int *i,
									t_env *_env)
{
	char *tmp;

	if (is_single_quote((*command)->array[y][*i]) && !(*flag))
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;
		(*command)->array[y] = treat_single_quote(tmp, i, flag);
	}
	if (is_double_quote((*command)->array[y][*i]) && !(*flag))
	{
		tmp = ft_strdup((*command)->array[y]);
		free((*command)->array[y]);
		(*command)->array[y] = NULL;
		(*command)->array[y] = treat_double_quote(tmp, i, _env, flag);
	}
	return ;
}

void		check_specials(t_command **command, t_env *_env)
{

	int		y;
	int		i;
	int		flag;

	y = 0;
	while ((*command)->array && (*command)->array[y])
	{
		i = 0;
		while ((*command)->array && (*command)->array[y] &&
			(*command)->array[y][i])
		{
			flag = 0;
			check_if_quotes(command, &flag, y, &i, _env);
			if (!is_single_quote((*command)->array[y][i]) &&
				!is_double_quote((*command)->array[y][i]) && !flag)
				if_no_quote(command, _env, y, &i);
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
