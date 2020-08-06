/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   character_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/06 13:19:47 by maran         #+#    #+#                 */
/*   Updated: 2020/08/06 15:06:16 by maran         ########   odam.nl         */
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

/*
** & and quotes are accepted characters in words.
** To do:
**  - \n nog toevoegen?
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
** A metacharacter:
** 			- A character that, when unquoted, separates words.
**			A metacharacter is a whitespace, or one of the following
**			characters: | & ; ( ) < >
** TO DO: 
**  - & en () voor nu eruit gelaten? 
*/

int				is_metachar(char c)
{
	if (is_whitespace(c) || is_operator(c))
		return (1);
	else
		return (0);
	
}
