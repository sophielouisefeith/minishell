/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 12:52:49 by msiemons      #+#    #+#                 */
/*   Updated: 2020/07/21 10:53:50 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			get_token_type(char *line, int *i)
{
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

static void			save_general(char *line, int *i, int type, t_lexer **head)
{
	t_lexer		*tmp;
	char		*str;
	int 		start;
	int 		len;

	start = *i;
	(*i)++;
	while (((get_token_type(line, i)) == token_general) && line[*i])
		(*i)++;
	len = *i - start;
	
	str = ft_substr(line, start, len);
	// if (str == 0)
	// 	error();
	tmp = ll_new_node(str, type);
	// if (tmp == 0)
	// 	error();
	ll_lstadd_back(head, tmp);
	(*i)--;
}

static void			save_quotation(char *line, int *i, int type, t_lexer **head)
{
	t_lexer		*tmp;
	char		*str;
	int 		start;
	int 		len;

	start = *i;
	(*i)++;
	while (line[start] != line[*i] && line[*i])			//Check of " " compleet is
		(*i)++;
	if (line[start] == line[*i])
	{
		if (is_general(line[*i + 1]))					// check of teken na " een splitting char is (white space of opertar)
		{
			(*i)++;
			while (is_general(line[*i]))
				(*i)++;
		}
		len = (*i - start) + 1;
		str = ft_substr(line, start, len);
		// if (str == 0)
		// 	error();
		tmp = ll_new_node(str, type);
		// if (tmp == 0)
		// 	error();
		ll_lstadd_back(head, tmp);
	}
	else
	{
		printf("[Multiple line command is not part of the subject\n]");
		exit(1);
	}
}

static void			save_operator(char *line, int *i, int type, t_lexer **head)
{
	t_lexer		*tmp;
	char 		*str;

	if (type == token_redirection_greater && line[*i + 1] == '>')
	{
		(*i)++;
		type = token_redirection_dgreater;
		str = str_redirection_dgreater();					//FREE!
	}
	else
		str = str_from_char(line[*i]);						//FREE!
	tmp = ll_new_node(str, type);
	ll_lstadd_back(head, tmp);
}

void				lexer(char *line)
{
	t_lexer		*head;
	t_lexer		*list;
	int 		type;
	int 		i;

	head = NULL;
	i = 0;
	while (line[i])
	{
		while (is_whitespace(line[i]))
			i++;
		type = get_token_type(line, &i);
		if (type == token_quote || type == token_dquote)
			save_quotation(line, &i, type, &head);
		if (type >= token_pipe && type <= token_redirection_lesser)
			save_operator(line, &i, type, &head);
		if (type == token_general)
			save_general(line, &i, type, &head);
		type = 0;
		i++;
	}

///
	list = head;
	printf("EIND RESULTAAT:\n");
	while (list)
	{
		printf("node-str = [%s], type[%d]\n", list->str, list->type);
		list = list->next;	
	}
///
}
