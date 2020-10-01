/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specials.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 17:40:26 by maran         #+#    #+#                 */
/*   Updated: 2020/10/01 22:27:08 by maran         ########   odam.nl         */
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

static char			*treat_double_quote(char *str, int *i, t_env *_env)
{
	int start;
	int end;

	start = *i;
	(*i)++; 
	while (str[*i] && str[*i] != '\"')
	{
		// printf(" [%d] [%c]\n", *i, str[*i]);
		if (str[*i] == '\\')
		{
			if (str[(*i) + 1] == '\"' || str[(*i) + 1] == '$')
				str = delete_escape_char(str, *i);
			if (str[(*i) + 1] == '$')
				(*i)++;
		}
		if (str[*i] == '$')
			str = if_dollar(str, *i, _env);
		(*i)++;
	}
	end = (*i)++;
	str = delete_double_quotes(str, start, end);
	*i = end--;
	return (str);
}

static char			*treat_single_quote(char *str, int *i)
{
	(*i)++;
	while (str[*i] && str[*i] != '\'')
		(*i)++;
	(*i)--;
	str = delete_quotes(str, '\'');				//Freeen oude malloc?
	return (str);
}

//GEBLEVEN BIJ DOUBLE EN GEEN QUOTES: TESTEN
void							check_specials(t_command **command, t_env *_env)
{
	int y;
	int i;

	y = 0;
	while ((*command)->array && (*command)->array[y])
	{
		i = 0;
		while((*command)->array[y][i])
		{
			if (is_single_quote((*command)->array[y][i]))
				(*command)->array[y] = treat_single_quote((*command)->array[y], &i);
			// printf("*** (*command)->array[y][%d] = [%c]\n", i, (*command)->array[y][i]);
			if (is_double_quote((*command)->array[y][i]))
				(*command)->array[y] = treat_double_quote((*command)->array[y], &i, _env);		//wat als na "" single quotes komen?
			if (!is_single_quote((*command)->array[y][i]) && !is_double_quote((*command)->array[y][i]))
			{
				if ((*command)->array[y][i] == '\\')
				{
					(*command)->array[y] = delete_escape_char((*command)->array[y], i);
					i++;
				}
				if ((*command)->array[y][i] == '$')
					(*command)->array[y]  = if_dollar((*command)->array[y] , i, _env);
			}
			i++;
		}
		y++;
	}
}