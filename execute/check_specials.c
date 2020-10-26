/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specials.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 17:40:26 by maran         #+#    #+#                 */
/*   Updated: 2020/10/26 12:11:55 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** TO DO:
	- Single quotes: //Freeen oude malloc?
	!!! - Check_builtin_again:  Misschien in if_dollar zetten. Zo niet ook onder andere if_dollars zetten! (wacht op andere aanpassingen).	
*/

/*
** In dubbel quotes:
**	- Outer dubbel quotes have te be complete (checked in lexer)
** 	- Inner single quotes are considered as text, don't have to be complete.
*/

static char		*treat_double_quote(char *str, int *i, t_env *_env, int *flag)
{
	int		dollar;
	int		start;
	int		end;

	start = *i;
	dollar = 0;
	if (str[*i - 1] == '$')
		dollar = 1;
	str = check_backslash_and_dollar(str, i, _env);
	end = *i;
	str = delete_double_quotes(str, start, end);
	*i = end - 2;
	*flag = 1;
	if (dollar == 1)
		str = ft_substr(str, 1, ft_strlen(str));
	return (str);
}

static char		*treat_single_quote(char *str, int *i, int *flag)
{
	int		end;
	int		dollar;
	
	if (str[*i - 1] == '$')
		dollar = 1;
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	end = *i;
	str = delete_quotes(str, '\'');
	*i = end - 2;
	*flag = 1;
	if (dollar == 1)
		str = ft_substr(str, 1, ft_strlen(str));
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
		(*command)->array[y] = delete_escape_char(tmp, *i);
		(*i)++;
	}
	if ((*command)->array[y][*i] == '$' &&
			(*command)->array[y][*i + 1] == '\\')							//Deze kan ik misschien nog samenvoegen met die daarboven 
	{
		(*command)->array[y] = delete_escape_char((*command)->array[y],
													 (*i + 1));
		(*i)++;
	}
	if ((*command)->array[y][*i] == '$')
	{
		(*command)->array[y]  = if_dollar((*command)->array[y] , i, _env, 0);
		check_builtin_again(command, _env, y);
	}
}

static void		check_if_quotes(t_command **command, int *flag, int y, int *i,
									t_env *_env)
{
	if (is_single_quote((*command)->array[y][*i]) && !(*flag))
		(*command)->array[y] = treat_single_quote((*command)->array[y], i,
													flag);
	if (is_double_quote((*command)->array[y][*i]) && !(*flag))
		(*command)->array[y] = treat_double_quote((*command)->array[y], i,
													_env, flag);
}

void			check_specials(t_command **command, t_env *_env)
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
				break;
			}
			i++;
		}	
		y++;
	}
}
