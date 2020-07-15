/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/03 21:06:57 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/15 13:42:59 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	size_t			i;
	char			*j;

	i = 0;
	j = malloc(size * count);
	if (!j)
		return (0);
	while (i < (count * size))
	{
		j[i] = 0;
		i++;
	}
	return (j);
}
