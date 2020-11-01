/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_general.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 16:45:57 by msiemons      #+#    #+#                 */
/*   Updated: 2020/11/01 17:05:56 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			*tmp_tolower(char *str)
{
	char		*tmp;
	int			i;

	i = 0;
	tmp = ft_strdup(str);
	while (str[i] != '\0')
	{
		tmp[i] = ft_tolower(str[i]);
		i++;
	}
	return (tmp);
}
