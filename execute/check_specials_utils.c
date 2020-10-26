/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specials_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 17:40:26 by maran         #+#    #+#                 */
/*   Updated: 2020/10/26 12:10:46 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** TO DO:
** 	- Moet er wel gemalloct worden bij delete_escape_char en delete_double_quotes?
*/

char			*delete_escape_char(char *src, int n)
{
	char	*dst;
	int		dst_i;
	int		src_i;
	int 	len;

	src_i = 0;
	dst_i = 0;
	len = ft_strlen(src) - 1;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	while (src[src_i] != '\0')
	{
		if (src_i == n)
			src_i++;
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
    dst[len] = '\0';
	free(src);		//leaks
	return (dst);
}

char			*delete_double_quotes(char *src, int start, int end)
{
	char	*dst;
	int		dst_i;
	int		src_i;
	int		len;

	src_i = 0;
	dst_i = 0;
	len = ft_strlen(src) - 2;
	dst = (char *)malloc(sizeof(char) * (len + 1));
	while (src[src_i] != '\0')
	{
		if (src_i == start || src_i == end)
		{
			src_i++;
			if (src_i == end)
				src_i++;
		}
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
	dst[len] = '\0';
	free(src);	//LEAKS
	src = NULL;	//LEAKS
	return (dst);
}

/*
**	- Escape character stills work in case of $ and \": 
**		* $: Operation of $ is gone and \ will be deleted.
**		* \":  the \ will be deleted. And " doesn't count as "has to be complete"
**		* Other: the \ will not be deleted.
*/

char			*check_backslash_and_dollar(char *str, int *i, t_env *_env)
{
	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{		
		if (str[*i] == '\\')
		{
			if (str[(*i) + 1] == '\"' || str[(*i) + 1] == '$' ||
				str[(*i) + 1] == '\\' || str[(*i) + 1] == 96)
				str = delete_escape_char(str, *i);
			if (str[(*i)] == '$')
				(*i)++;
		}
		if (str[*i] == '$')
			str = if_dollar(str, i, _env, 1);
		(*i)++;	
	}
	return (str);
}
