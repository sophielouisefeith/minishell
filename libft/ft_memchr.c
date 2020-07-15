/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_memchr.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/10/30 16:19:09 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/15 12:22:44 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ps;
	unsigned char	a;
	size_t			i;

	ps = (unsigned char *)s;
	a = c;
	i = 0;
	while (i < n)
	{
		if (ps[i] == a)
			return (ps + i);
		i++;
	}
	return (NULL);
}
