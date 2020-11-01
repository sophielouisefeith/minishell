/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_specials_utils.c                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/01 17:40:26 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 20:36:15 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*delete_escape_char(char *src, int n)
{
	char	*dst;
	int		dst_i;
	int		src_i;
	int		len;

	src_i = 0;
	dst_i = 0;
	len = ft_strlen(src) - 1;
	dst = (char *)calloc((len + 1), sizeof(char));
	while (src[src_i] != '\0')
	{
		if (src_i == n)
			src_i++;
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
	dst[len] = '\0';
	free(src);
	src = NULL;
	return (dst);
}

static	char	*final_delete(char *dst, char *src, int len)
{
	dst[len] = '\0';
	free(src);
	src = NULL;
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
	dst = (char *)calloc((len + 1), sizeof(char));
	while (src[src_i] != '\0')
	{
		if (src_i == start || src_i == end)
		{
			src_i++;
			if (src_i == end)
				src_i++;
			if (!src[src_i])
				break ;
		}
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
	return (final_delete(dst, src, len));
}

static void		if_dollar_back(char *str, char *tmp, int *i)
{
	if (str[*i] == '\\')
	{
		if (str[(*i) + 1] == '\"' || str[(*i) + 1] == '$' ||
			str[(*i) + 1] == '\\' || str[(*i) + 1] == 96)
		{
			tmp = ft_strdup(str);
			free(str);
			str = NULL;
			str = delete_escape_char(tmp, *i);
		}
		if (str[(*i)] == '$')
			(*i)++;
	}
}

char			*check_backslash_and_dollar(char *str, int *i, t_env *envb)
{
	char	*tmp;

	(*i)++;
	while (str[*i] && str[*i] != '\"')
	{
		if_dollar_back(str, tmp, i);
		if (str[*i] == '$')
		{
			tmp = ft_strdup(str);
			free(str);
			str = NULL;
			str = if_dollar(tmp, i, envb, 1);
		}
		(*i)++;
	}
	return (str);
}
