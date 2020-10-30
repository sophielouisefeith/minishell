/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   char_check.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/30 15:56:12 by maran         #+#    #+#                 */
/*   Updated: 2020/10/30 15:56:15 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** & and quotes are accepted characters in words.
*/

int				is_operator(char c)
{
	if (c == ';')
		return (token_semicolon);
	if (c == '|')
		return (token_pipe);
	if (c == '>')
		return (token_redirection_greater);
	if (c == '<')
		return (token_redirection_lesser);
	else
		return (0);
}

/*
** A metacharacter is a char that, when unquoted, separates words.
** It's is a whitespace, or one of the following characters:
** | & ; ( ) < >
*/

int				is_metachar(char c)
{
	if (is_whitespace(c) || is_operator(c))
		return (1);
	else
		return (0);
}
