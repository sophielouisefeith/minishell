/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 15:51:41 by msiemons      #+#    #+#                 */
/*   Updated: 2020/07/20 16:16:22 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int				is_whitespace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t' || c == '\r' || c == '\v'
			|| c == '\f')
		return (1);
	return (0);
}

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

char 			*str_from_char(char c)
{
	char 	*str;
	str = (char *)malloc(sizeof(char) * 2);

	str[0] = c;
	str[1] = '\0';

	return (str);
}

char 			*str_redirection_dgreater(void)
{
	char 	*str;
	str = (char *)malloc(sizeof(char) * 3);
	str = ">>";

	return (str);
}
