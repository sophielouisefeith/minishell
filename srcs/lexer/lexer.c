/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maran <maran@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 12:52:49 by msiemons          #+#    #+#             */
/*   Updated: 2020/11/04 13:51:07 by maran            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		check_quotation_complete(char quote, char *line, int *i)
{
	(*i)++;
	while (line[*i] != quote && line[*i])
	{
		if (is_backslash(line[*i]) && is_double_quote(line[(*i) + 1]) &&
				!is_backslash(line[(*i) - 1]))
			(*i)++;
		(*i)++;
	}
	if (line[*i] == quote)
		return ;
	else
	{
		not_part(line);
		g_own_exit = 3;
		g_exit_status = 1;
	}
}

static void		check_meta_and_quote(char *line, int *i)
{
	while ((!is_metachar(line[*i])) && line[*i])
	{
		if ((is_single_quote(line[*i]) || is_double_quote(line[*i])) &&
				line[(*i) - 1] != '\\')
			check_quotation_complete(line[*i], line, i);
		(*i)++;
	}
}

static void		save_word(char *line, int *i, t_lexer **sort)
{
	t_lexer		*tmp;
	char		*str;
	int			*token;
	int			start;

	start = *i;
	token = allocate_memory_int_string(12);
	token[token_general] = 1;
	check_meta_and_quote(line, i);
	str = ft_substr(line, start, (*i - start));
	tmp = ll_new_node_lexer(str, token);
	ll_lstadd_back_lexer(sort, tmp);
}

static void		save_operator(char *line, int *i, int type, t_lexer **sort)
{
	t_lexer		*tmp;
	char		*str;
	int			*token;

	token = allocate_memory_int_string(12);
	if (type == token_redirection_greater && line[*i + 1] == '>')
	{
		(*i)++;
		token[token_redirection_dgreater] = 1;
		str = str_redirection_dgreater();
	}
	else
	{
		token[type] = 1;
		str = str_from_char(line[*i]);
	}
	if (type >= token_redirection_greater &&
			type <= token_redirection_dgreater)
		token[token_redirection] = check_redirections(line, *i, type);
	tmp = ll_new_node_lexer(str, token);
	ll_lstadd_back_lexer(sort, tmp);
	(*i)++;
}

void			lexer(t_lexer **sort, char *line)
{
	int			type;
	int			i;

	i = 0;
	while (line[i] && g_own_exit != 3)
	{
		while (is_whitespace(line[i]))
			i++;
		type = get_token_type(line, &i);
		if (type == token_general)
			save_word(line, &i, sort);
		if (type >= token_pipe && type <= token_redirection_lesser)
			save_operator(line, &i, type, sort);
		type = 0;
	}
}
