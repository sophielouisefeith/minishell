/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memset.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/29 10:10:23 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/18 17:56:07 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char *b1;

	b1 = (unsigned char *)b;
	while (len)
	{
		*b1 = (unsigned char)c;
		b1++;
		len--;
	}
	return (b);
}
