/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/09 18:41:09 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/25 14:38:03 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_count(long n)
{
	int		i;

	i = 0;
	if (n < 0)
	{
		i++;
		n = n * -1;
	}
	if (n == 0)
		return (1);
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char			*ft_itoa(int n)
{
	int			j;
	char		*res;
	long		nb;

	nb = n;
	j = ft_count(nb);
	res = malloc(sizeof(char) * (j + 1));
	if (res == NULL)
		return (NULL);
	res[j] = '\0';
	j--;
	if (nb == 0)
		res[0] = 48;
	if (nb < 0)
	{
		res[0] = '-';
		nb = -nb;
	}
	while (nb > 0)
	{
		res[j] = (nb % 10) + 48;
		nb = nb / 10;
		j--;
	}
	return (res);
}
