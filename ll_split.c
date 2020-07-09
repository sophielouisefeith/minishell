/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 10:08:48 by msiemons      #+#    #+#                 */
/*   Updated: 2020/07/09 11:37:56 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static int			count_splits(const char *s, char c)
{
	int 	i;
	int 	count;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			count++;
			while (s[i] != c && s[i])
				i++;
		}
		while (s[i] == c)
			i++;
	}
	return (count);
}

static int			start(const char *s, char c, int i, size_t len)
{
	i = i + len;
	while (s[i] == c)
		i++;
	return (i);
}

static int			end(const char *s, char c, int i)
{
	size_t 	len;

	len = 0;
	while (s[i] && s[i] != c)
	{
		i++;
		len++;
	}
	return (len);
}

void				ll_split(t_parse **head, char const *s, char c)
{
	size_t		len;
	int			count;
	int			i;
	t_parse		*tmp;
	
	i = 0;
	len = 0;
	if (!s)
		return ;
	count = count_splits(s, c);
	while (count > 0)
	{
		i = start(s, c, i, len);
		len = end(s, c, i);
		tmp = ll_new_node(ft_substr(s, i, len));
		// if (tmp == 0)
		// 	strerror()
		ll_lstadd_back(head, tmp);
		count--;
	}
}
