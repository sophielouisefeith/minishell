/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 10:08:48 by msiemons      #+#    #+#                 */
/*   Updated: 2020/07/07 14:05:06 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

static	int		ft_count(const char *s, char c)
{
	int i;
	int count;

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

static	int		ft_start(const char *s, char c, int i, size_t len)
{
	i = i + len;
	while (s[i] == c)
		i++;
	return (i);
}

static	int		ft_end(const char *s, char c, int i)
{
	size_t len;

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
	int		count;
	t_parse	*head;
	int		i;
	int		y;
	size_t	len;

	i = 0;
	y = 0;
	len = 0;
	if (!s)
		return (NULL);
	count = ft_count(s, c);
	while (y < count)
	{
		i = ft_start(s, c, i, len);
		len = ft_end(s, c, i);
		ll_list_push_front(&head, ft_substr(s, i, len));
		y++;
	}
	return (head);
}
