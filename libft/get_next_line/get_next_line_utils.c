/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line_utils.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:37:28 by msiemons      #+#    #+#                 */
/*   Updated: 2020/11/06 15:16:19 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

char			*ft_strchr_gnl(const char *s, int c)
{
	int		i;
	char	c1;

	i = 0;
	c1 = c;
	while (s[i] != '\0')
	{
		if (s[i] == c1)
			return ((char *)s + i);
		i++;
	}
	if (c1 == '\0')
		return ((char *)s + i);
	return (NULL);
}

char			*ft_substr_gnl(char *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;
	size_t	strlen_s;

	i = 0;
	if (!s)
		return (NULL);
	strlen_s = ft_strlen(s);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
	{
		free(s);
		return (NULL);
	}
	while (i < len && start < strlen_s)
	{
		dest[i] = s[start];
		i++;
		start++;
	}
	dest[i] = '\0';
	return (dest);
}

/*
** Beginning of strjoin
*/

static	char	*ft_strpaste(char *dest, char const *src1, char const *src2)
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

char			*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	size_t	len;

	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (str == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_strpaste(str, s1, s2);
	free(s1);
	free(s2);
	s1 = NULL;
	s2 = NULL;
	return (str);
}
