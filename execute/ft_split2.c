/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_split2.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/12 10:08:48 by msiemons      #+#    #+#                 */
/*   Updated: 2020/10/30 15:26:55 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char			**ft_split2(char const *s, char c)
{
	char	**array;
	char 	*split;
	int 	len;

	if (!s)
		return (NULL);
	array = (char **)malloc((3) * sizeof(char *));
	if (array == NULL)
		return (NULL);
	split = ft_strchr(s, c);
	len =  &(*split) - &(*s);
	array[0] = ft_substr(s, 0, len);
	array[1] = ft_substr(s, len + 1, ft_strlen(s));
	if (array)
		array[2] = 0;
	return (array);
}
