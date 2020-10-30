/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   character_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 13:19:47 by maran         #+#    #+#                 */
/*   Updated: 2020/10/30 15:44:27 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				is_whitespace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' || c == '\f' || c == '\r'
			|| c == ' ')
		return (1);
	return (0);
}

int				is_single_quote(char c)
{
	if (c == '\'')
		return (1);
	else
		return (0);
}

int				is_double_quote(char c)
{
	if (c == '\"')
		return (1);
	else
		return (0);
}

int				is_backslash(char c)
{
	if (c == '\\')
		return (1);
	else
		return (0);
}
