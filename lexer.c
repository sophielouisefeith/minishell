/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 12:52:49 by msiemons      #+#    #+#                 */
/*   Updated: 2020/08/03 19:16:58 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** >>>>>>> TO DO <<<<<<<<<<<<<< 
** 1. get_token_type: wss splitten op words vs operator hier voldoende (niet op alle subs).
** 2. *token strings toegevoegd aan code. Beste methode? Ontdekken we vast bij parsing.
** 3. Protecten, error-exit, free
** 4. Let op: niet te veel parameters in fucnties: opschonen.
*/

int			get_token_type(char *line, int *i)
{
	if (is_whitespace(line[*i]))
		return (token_whitespace);
	else if (is_single_quote(line[*i]))
		return (token_quote);
	else if (is_double_quote(line[*i]))
		return (token_dquote);
	else if (is_operator(line[*i]))
		return (is_operator(line[*i]));
	else if (line[*i] == '\0')
		return (token_null);
	else
		return (token_general);
}

static int			check_quotation_complete(char quote, char *line, int *i, int *token)
{
	(*i)++;
	while (line[*i] != quote && line[*i])
	{
		if (line[*i] == '$')
			token[token_dollar] = 1;
		if (line[*i] == 92 && line[(*i)++] == '\"')
			(*i)++;
		(*i)++;
	}
	if (line[*i] == quote)
		return (0);
	else
	{
		printf("[Multiple line command is not part of the subject\n]");
		exit(1);
	}
}

static int		check_meta_and_quote(char *line, int *i, int *token)
{
	while (!is_metachar(line[*i]) && line[*i])
	{
		if (is_single_quote(line[*i]))
		{
			token[token_quote] = 1;
			check_quotation_complete(line[*i], line, i, token);
		}
		if (is_double_quote(line[*i]))
		{
			token[token_dquote] = 1;
			check_quotation_complete(line[*i], line, i, token);
		}
		if (line[*i] == '$')
			token[token_dollar] = 1;
		(*i)++;
	}
	return (0);
}

int				*intspace(int i)
{
	int 	*size_type;

	size_type = (int *)malloc(sizeof(int) * i);
	ft_bzero(size_type, 11 * sizeof(int));

	return (size_type);
}

static void			save_word(char *line, int *i, t_lexer **head)
{
	t_lexer		*tmp;
	char		*str;
	int			start;
	int			len;
	int			*token;

	start = *i;
	token = intspace(11);
	token[token_general] = 1;
	check_meta_and_quote(line, i, token);
	len = *i - start;
	str = ft_substr(line, start, len);
	tmp = ll_new_node(str, token);
	ll_lstadd_back(head, tmp);
}

/*
** Later kijken of deze manier van type doorgeven nog handig is.
*/

static void			save_operator(char *line, int *i, int type, t_lexer **head)
{
	t_lexer		*tmp;
	char		*str;
	int			*token;

	token = intspace(12);
	if (type == token_redirection_greater && line[*i + 1] == '>')
	{
		(*i)++;
		token[token_redirection_dgreater] = 1;
		str = str_redirection_dgreater();					//FREE!
	}
	else
	{
		token[type] = 1;
		str = str_from_char(line[*i]);						//FREE!
	}
	if (type >= token_redirection_greater && type <= token_redirection_dgreater)
		token[token_redirection] = 1; 
	tmp = ll_new_node(str, token);
	ll_lstadd_back(head, tmp);
	(*i)++;
}

void				lexer(char *line)
{
	t_lexer		*head;
	t_lexer		*list;
	
	int 		type;
	int 		i;
	int			count;

	count = 0;
	head = NULL;
	i = 0;
	while (line[i])
	{
		while (is_whitespace(line[i]))
			i++;
		type = get_token_type(line, &i);
		if (type == token_quote || type == token_dquote || type == token_general)
			save_word(line, &i, &head);
		if (type >= token_pipe && type <= token_redirection_lesser)
			save_operator(line, &i, type, &head);
		type = 0;
	}

/// TESTER
	// printf("value head = [%p], adress head = [%p]\n", head, &head);
	list = head;
	printf("EIND RESULTAAT:\n");
	//int n;
	int k;
	k = 0;
	while (head)
	{
		k = transform(&head, count);
		if (k == 1)
			count = 1;
		else
			count = 0;
		if (head)
			head = head->next;
		
	}
/// TESTER
	list = head;
	printf("EIND RESULTAAT:\n");
	int n;
	while (list)
	{
		//transform(list);										// this is the expiriment with transform ffrom sophie 
		// printf("node-str = [%s]\n", list->str);
		// n = 0;
		// while (n < 11)
		// {
		// 	printf("%d=[%d]  ", n, list->token[n]);
		// 	n++;
		// }
		// printf("\n");
		list = list->next;	
	}
/// END TESTER
}
