/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memcpy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 15:05:40 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/18 15:46:50 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char			*dst1;
	unsigned const char		*src1;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned const char *)src;
	if (dst == src)
		return (dst);
	while (n)
	{
		*dst1 = *src1;
		dst1++;
		src1++;
		n--;
	}
	return (dst);
}
