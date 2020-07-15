/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_strtrim.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2019/11/07 14:08:26 by sfeith         #+#    #+#                */
/*   Updated: 2019/11/25 15:25:20 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	end;
	size_t	start;
	char	*str;

	start = 0;
	if (!s1 || !set)
		return (NULL);
	end = ft_strlen(s1);
	while (s1[start] != '\0')
	{
		if (ft_strchr(set, s1[start]) == NULL)
			break ;
		start++;
	}
	if (s1[start] == '\0')
		return (ft_strdup(""));
	while (end)
	{
		if (ft_strchr(set, s1[end - 1]) == NULL)
			break ;
		end--;
	}
	end = end - start;
	str = ft_substr((char *)s1, start, end);
	return (str);
}
