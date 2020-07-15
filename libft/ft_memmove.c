/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memmove.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 11:19:41 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/18 16:21:44 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char			*dst1;
	unsigned const char		*src1;

	dst1 = (unsigned char *)dst;
	src1 = (unsigned const char *)src;
	if (dst == NULL && src == NULL)
		return (NULL);
	if (dst > src)
	{
		while (len)
		{
			len--;
			dst1[len] = src1[len];
		}
	}
	else
		ft_memcpy(dst, src, len);
	return (dst);
}
