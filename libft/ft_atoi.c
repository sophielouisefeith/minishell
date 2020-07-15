/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_atoi.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/01 09:55:46 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/24 17:09:11 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	int						i;
	unsigned long long		b;
	int						mp;

	i = 0;
	b = 0;
	mp = 1;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-')
		mp = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && (str[i] <= '9'))
	{
		if (b >= 9223372036854775808ULL && mp == 1)
			return (-1);
		if (b >= 9223372036854775809ULL && mp == -1)
			return (0);
		b = b * 10 + str[i] - '0';
		i++;
	}
	return ((int)mp * b);
}
