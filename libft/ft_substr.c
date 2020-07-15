/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_substr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/06 14:23:38 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/25 14:37:00 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	srclen;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	srclen = ft_strlen(s);
	if (start >= srclen)
		return (ft_strdup(""));
	if (srclen - start < len)
		len = srclen - start;
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (sub == NULL)
		return (NULL);
	ft_strlcpy(sub, s + start, len + 1);
	return (sub);
}
