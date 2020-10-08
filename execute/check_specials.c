/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specials.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 17:40:26 by maran         #+#    #+#                 */
/*   Updated: 2020/10/08 16:12:19 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char		*delete_escape_char(char *src, int n)
{
	char *dst;
	int dst_i;
	int src_i;
	int len;

	src_i = 0;
	dst_i = 0;
	len = ft_strlen(src) - 1;
	dst = (char *)malloc(sizeof(char) * (len + 1));			//New: gaat dit goed, moet ik wel opnieuw mallocen. Let op bij freeen. 
	while (src[src_i] != '\0')
	{
		if (src_i == n)
			src_i++;
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
    dst[len] = '\0';
	return (dst);
}


static char		*delete_double_quotes(char *src, int start, int end)
{
	char *dst;
	int dst_i;
	int src_i;
	int len;

	src_i = 0;
	dst_i = 0;
	len = ft_strlen(src) - 2;
	dst = (char *)malloc(sizeof(char) * (len + 1));			//New: gaat dit goed, moet ik wel opnieuw mallocen. Let op bij freeen. 
	while (src[src_i] != '\0')
	{
		if (src_i == start || src_i == end)
			src_i++;
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
    dst[len] = '\0';
	return (dst);
}

/*
** Moet buitenste quotes op een andere manier verwijderen dan voorheen, omdat er ook quotes in het midden kunnen staan
Nadat echo "hallo\"\poep" --> \ wordt verwijderd, maar \poep wordt nog wel geprint alsof het binnen haakjes staat.
** Kijken of andere methode ook naar start end methode kan.
*/

/*
** In dubbel quotes:
**	- Outer dubbel quotes have te be complete (checked in lexer)
**	- Escape character stills work in case of $ and \": 
**		* $: Operation of $ is gone and \ will be deleted.
**		* \":  the \ will be deleted. And " doesn't count as "has to be complete"
**		* Other: the \ will not be deleted.
** 	- Inner single quotes are considered as text, don't have to be complete.
*/

static char			*treat_double_quote(char *str, int *i, t_env *_env, int *flag)
{
	int start;
	int end;

	start = *i;
	(*i)++; 
	while (str[*i] && str[*i] != '\"')
	{
		if (str[*i] == '\\')
		{
			if (str[(*i) + 1] == '\"' || str[(*i) + 1] == '$')
				str = delete_escape_char(str, *i);
			if (str[(*i)] == '$')
				(*i)++;
		}
		if (str[*i] == '$')
			str = if_dollar(str, *i, _env);
		(*i)++;
	}
	end = *i;										// waarom stond dit erachter? ++;
	str = delete_double_quotes(str, start, end);
	*i = end - 2; 					// beter niet -1 want beter laten eindigen op laatste char van deze reeks.
	*flag = 1;
	return (str);
}

static char			*treat_single_quote(char *str, int *i, int *flag)
{
	int end;

	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	end = *i;
	str = delete_quotes(str, '\'');				//Freeen oude malloc?
	*i = end - 2;
	*flag = 1;
	return (str);
}

/*
** Check_builtin_again: check _env variables ($) for commands.
** Ex. export LS="ls -la" 
**
TO DO:
- Check_builtin_again:  Misschien in if_dollar zetten. Zo niet ook onder andere if_dollars zetten! (wacht op andere aanpassingen).
*/

void							check_specials(t_command **command, t_env *_env)
{
	int y;
	int i;
	int flag;

	y = 0;
	while ((*command)->array && (*command)->array[y])
	{
		i = 0;
		while((*command)->array && (*command)->array[y] && (*command)->array[y][i]) 			//of gewoon break gebruiken?
		{
			flag = 0;
			if (is_single_quote((*command)->array[y][i]) && !flag)
				(*command)->array[y] = treat_single_quote((*command)->array[y], &i, &flag);
			if (is_double_quote((*command)->array[y][i]) && !flag)
				(*command)->array[y] = treat_double_quote((*command)->array[y], &i, _env, &flag);
			if (!is_single_quote((*command)->array[y][i]) && !is_double_quote((*command)->array[y][i]) && !flag)
			{
				if ((*command)->array[y][i] == '\\')
				{
					(*command)->array[y] = delete_escape_char((*command)->array[y], i);
					i++;
				}
				if ((*command)->array[y][i] == '$')
				{
					(*command)->array[y]  = if_dollar((*command)->array[y] , i, _env);
					check_builtin_again(command, _env, y);
				}
			}
			if ((*command)->array[y] == NULL)
				parameter_not_exist(command, &y);
			i++;
		}
		y++;
	}
}