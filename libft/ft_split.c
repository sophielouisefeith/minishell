/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 09:31:07 by sfeith         #+#    #+#                */
/*   Updated: 2019/12/04 15:47:37 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_wordcount(char const *s, char c)
{
	int		i;
	int		wcount;

	i = 0;
	wcount = 0;
	if (c == '\0' && s[i] != '\0')
		return (1);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			wcount++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
		while (s[i] == c)
			i++;
	}
	return (wcount);
}

static int		ft_lettercount(char const *s, char c, int i)
{
	int	count;

	count = 0;
	while (s[i] != '\0' && s[i] == c)
		i++;
	while (s[i] != '\0' && s[i] != c)
	{
		count++;
		i++;
	}
	return (count);
}

static char		**ft_freenewstring(char **ns, int j)
{
	while (j >= 0)
	{
		j--;
		if (ns[j])
			free(ns[j]);
	}
	if (ns)
		free(ns);
	return (NULL);
}

static char		**ft_newstring(char const *s, char c, char **ns)
{
	int i;
	int lcount;
	int j;

	j = 0;
	i = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c && s[i] != '\0')
			i++;
		if (s[i] != c && s[i] != '\0')
		{
			lcount = ft_lettercount(s, c, i);
			ns[j] = ft_substr((char *)s, i, (size_t)lcount);
			if (ns[j] == 0)
				return (ft_freenewstring(ns, j));
			j++;
			while (s[i] != c && s[i] != '\0')
				i++;
		}
	}
	return (ns);
}

char			**ft_split(char const *s, char c)
{
	int		i;
	char	**words;
	int		wc;

	if (!s)
		return (NULL);
	i = 0;
	wc = ft_wordcount(s, c);
	words = ((char**)malloc((wc + 1) * sizeof(char *)));
	if (words == NULL)
		return (NULL);
	words = ft_newstring(s, c, words);
	words[wc] = NULL;
	return (words);
}
