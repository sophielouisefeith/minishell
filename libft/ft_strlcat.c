/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strlcat.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/03 18:40:37 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/25 11:14:12 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_strnlen(const char *s, size_t dstsize)
{
	size_t i;

	i = 0;
	while (s[i] != '\0' && i < dstsize)
		i++;
	return (i);
}

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t dstlen;
	size_t srclen;

	dstlen = ft_strnlen(dst, dstsize);
	srclen = ft_strlen(src);
	if (dst == NULL)
		return (srclen);
	if (dstlen > dstsize)
		return (dstsize + srclen);
	ft_strlcpy(dst + dstlen, src, dstsize - dstlen);
	return (dstlen + srclen);
}
