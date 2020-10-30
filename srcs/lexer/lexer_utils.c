/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 15:51:41 by msiemons      #+#    #+#                 */
/*   Updated: 2020/10/30 21:21:06 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				check_redirections(char *line, int i, int type)
{
	i++;
	while (is_whitespace(line[i]))
		i++;
	if (type == token_redirection_greater ||
			type == token_redirection_dgreater)
	{
		if (line[i] == '/' || line[i] == '.' || line[i] == '~')
			return (error_redirections(line[i], 3, 0, NULL));
	}
	if (line[i] == '\n' || line[i] == '#' || line[i] == '&' ||
		line[i] == '(' || line[i] == ')' || line[i] == ';' ||
		line[i] == '>' || line[i] == '<' || line[i] == '|' || line[i] == '\0')
			return (error_redi_one(line[i], i, line));
			// return (error_redirections(line[i], 1,i, line));
	if (line[i] == '*')
		return (error_redirections(line[i], 2, 0, NULL));
	return (1);
}

int				get_token_type(char *line, int *i)
{
	int 		operator;

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
	int 		*int_str;

	int_str = (int *)calloc(i, sizeof(int));			//NEW TEST: Tijdens cleaning.
	return (int_str);
}

char 			*str_from_char(char c)
{
	char 		*str;

	str = (char *)malloc(sizeof(char) * 2);
	str[0] = c;
	str[1] = '\0';
	return (str);
}

char 			*str_redirection_dgreater(void)
{
	char		*str;

	str = (char *)malloc(sizeof(char) * 3);
	str[0] = '>';
	str[1] = '>';
	str[2] = '\0';										//NEW TEST: Tijdens cleaning.
	return (str);
}
