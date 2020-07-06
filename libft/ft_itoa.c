/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_itoa.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/04 15:16:54 by msiemons      #+#    #+#                 */
/*   Updated: 2019/11/11 19:13:55 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		ft_intlength(int n)
{
	int i;

	i = 0;
	if (n < 0)
		i++;
	while (n != 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static	void	ft_recursive_itoa(int n, char *str, int i)
{
	i = ft_intlength(n) - 1;
	if (n / 10 != 0)
		ft_recursive_itoa(n / 10, str, i);
	str[i] = (n % 10 + '0');
}

static	void	ft_negative(int n, char *dest, int len)
{
	ft_recursive_itoa((n * -1), dest, len);
	while (len > 0)
	{
		dest[len] = dest[len - 1];
		len--;
	}
	dest[0] = '-';
}

char			*ft_itoa(int n)
{
	char	*dest;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_intlength(n);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (dest == NULL)
		return (NULL);
	if (n > 0)
		ft_recursive_itoa(n, dest, len);
	if (n < 0)
		ft_negative(n, dest, len);
	dest[len] = '\0';
	return (dest);
}
