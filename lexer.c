/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 12:52:49 by msiemons      #+#    #+#                 */
/*   Updated: 2020/07/16 18:23:23 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void						save_general(char *line, int *i, int type, t_lexer **head)
{
	char		*str;
	int 		start;
	int 		len;
	t_lexer		*tmp;

	start = *i;
	(*i)++;
	while (((get_token_type(line, i)) == token_general) && line[*i])
		(*i)++;
	len = *i - start;
	str = ft_substr(line, start, len);
	// printf("substr = [%s]\n", str);
	// if (str == 0)
	// 	error();
	tmp = ll_new_node(str, type);
	// if (tmp == 0)
	// 	error();
	ll_lstadd_back(head, tmp);
}

static void						save_quotation(char *line, int *i, int type, t_lexer **head)
{
	char		*str;
	int 		start;
	int 		len;
	t_lexer		*tmp;

	start = *i;
	(*i)++;
	while (line[start] != line[*i])
		(*i)++;
	if (line[start] == line[*i])
	{
		len = (*i - start) + 1;
		str = ft_substr(line, start, len);
		// if (str == 0)
		// 	error();
		tmp = ll_new_node(str, type);
		// if (tmp == 0)
		// 	error();
		ll_lstadd_back(head, tmp);
	}
}

static void						save_operator(char *line, int *i, int type, t_lexer **head)
{
	t_lexer		*tmp;
	char 		str[2];

	if (type == token_redirection_greater && line[*i + 1] == '>')
	{
		(*i)++;
		type = token_redirection_dgreater;
		tmp = ll_new_node(">>", type);
	}
	else
	{
		str[0] = line[*i];
		str[1] = '\0';
		tmp = ll_new_node(str, type);
		ll_lstadd_back(head, tmp);
	}
}

int				get_token_type(char *line, int *i)
{
	int		ret;

	if (is_whitespace(line[*i]))
		return (token_whitespace);
	if (is_single_quote(line[*i]))
		return (token_quote);
	else if (is_double_quote(line[*i]))
		return (token_dquote);
	else if (is_operator(line[*i]))
		return (is_operator(line[*i]));
	else
		return (token_general);
}

void					lexer(char *line)
{
	t_lexer		*head;
	int 		type;
	int 		i;

	head = NULL;
	i = 0;
	while (line[i])
	{
		while (is_whitespace(line[i]))
			i++;
		type = get_token_type(line, &i);
		// printf("1: type = [%d], i = [%d]\n", type, i);
		if (type == token_quote || type == token_dquote)
			save_quotation(line, &i, type, &head);
		if (type >= token_pipe &&  type <= token_redirection_lesser)
			save_operator(line, &i, type, &head);
		if (type == token_general)
			save_general(line, &i, type, &head);
		type = 0;
		i++;
		// printf("2: type = [%d], i = [%d]\n", type, i);
	}
	while (head)
	{
		printf("node-str = [%s]\n", head->str);
		head = head->next;	
	}
}
