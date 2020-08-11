/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 15:51:41 by msiemons      #+#    #+#                 */
/*   Updated: 2020/08/11 16:53:03 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changelog:
** - Verwijderd:
	if (is_whitespace(line[*i]))
		return (token_whitespace);
	if (is_single_quote(line[*i]))
		return (token_quote);
	else if (is_double_quote(line[*i]))
		return (token_dquote);
** - Aangepast:
	if (is_operator(line[*i]))
		return (is_operator(line[*i]));
*/

int				get_token_type(char *line, int *i)
{
	int 	operator;

	operator = 0;
	operator = is_operator(line[*i]); 
	if (operator)
		return (operator);
	else if (line[*i] == '\0')
		return (token_null);
	else
		return (token_general);
}

int				*allocate_memory_int_string(int i)
{
	int 	*int_str;

	int_str = (int *)malloc(sizeof(int) * i);
	if(!int_str)
		error_free(12);
	ft_bzero(int_str, 11 * sizeof(int));
	return (int_str);
}

char 			*str_from_char(char c)
{
	char 	*str;

	str = (char *)malloc(sizeof(char) * 2);
	if(!str)
		error_free(12);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char 			*str_redirection_dgreater(void)
{
	char 	*str;

	str = (char *)malloc(sizeof(char) * 3);
	if(!str)
		error_free(12);
	str = ">>";
	return (str);
}
