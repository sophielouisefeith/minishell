/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strnstr.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 10:16:13 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/19 19:13:23 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	s;
	size_t	needle_len;

	i = 0;
	s = 0;
	if (needle[i] == '\0')
		return ((char*)haystack);
	needle_len = ft_strlen(needle);
	while (i < len && haystack[i] != '\0')
	{
		while (haystack[i + s] == needle[s] && haystack[i] != '\0' \
		&& (i + s) < len)
		{
			if (needle_len == s + 1)
				return ((char *)haystack + (i));
			s++;
		}
		i++;
		s = 0;
	}
	return (NULL);
}
