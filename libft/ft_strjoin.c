/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strjoin.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 11:58:42 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/25 14:36:50 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		*ft_strcpy(char *dest, char const *src1, char const *src2)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (src1[i] != '\0')
	{
		dest[i] = src1[i];
		i++;
	}
	while (src2[c] != '\0')
	{
		dest[i] = src2[c];
		i++;
		c++;
	}
	dest[i] = '\0';
	return (dest);
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	size_t		s1len;
	size_t		s2len;
	char		*ns;

	if (!s1 || !s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ns = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (ns == NULL)
		return (NULL);
	ft_strcpy(ns, s1, s2);
	return (ns);
}
