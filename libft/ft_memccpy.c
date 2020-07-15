/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memccpy.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 13:11:03 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/18 15:57:53 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*src1;
	unsigned char	*dst1;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned char *)src;
	while (n)
	{
		*dst1 = *src1;
		if (*dst1 == (unsigned char)c)
			return ((void *)(dst1 + 1));
		src1++;
		dst1++;
		n--;
	}
	return (NULL);
}
