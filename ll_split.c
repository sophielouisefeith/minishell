/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 10:08:48 by msiemons      #+#    #+#                 */
/*   Updated: 2020/07/07 16:24:14 by Maran         ########   odam.nl         */
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
	if (c == '\0' && s[i] != '\0')
		return (1);
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

t_parse				*ll_split(char const *s, char c)
{
	t_parse	*head;
	int		count;
	size_t	len;
	int		i;

	i = 0;
	len = 0;
	if (!s)
		return (NULL);
	count = count_splits(s, c);
	while (count > 0)
	{
		i = start(s, c, i, len);
		len = end(s, c, i);
		ll_list_push_front(&head, ft_substr(s, i, len));
		count--;
	}
	return (head);
}
