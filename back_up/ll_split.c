/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ll_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 10:08:48 by msiemons      #+#    #+#                 */
/*   Updated: 2020/07/15 23:35:33 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

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

/*
** name	 value	adress
** ----- ----- -----
** head | x970| ....| From here on I pass the value of the initial head (==address that will point to first node).
** Receive as a pointer pointer, so if the head is pointing to somewhat else the head in the parser function wil change aswell.
*/

void				ll_split(t_parse **head, char const *s, char c)
{
	t_parse		*tmp;
	size_t		len;
	char 		*str;
	int			count;
	int			i;

	i = 0;
	len = 0;
	if (!s)
		error();
	count = count_splits(s, c);
	while (count > 0)
	{
		i = start(s, c, i, len);
		len = end(s, c, i);
		str = ft_substr(s, i, len);
		if (str == 0)
			error();
		tmp = ll_new_node(str);
		if (tmp == 0)
			error();
		ll_lstadd_back(head, tmp);
		count--;
	}
}
