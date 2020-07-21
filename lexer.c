/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   lexer.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/16 12:52:49 by msiemons      #+#    #+#                 */
/*   Updated: 2020/07/21 14:52:05 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


/*
** Misschien ook mogelijk alleen te splitten op words vs operator. Later naar kijken.
*/

static int			get_token_type(char *line, int *i)
{
	if (is_whitespace(line[*i]))
		return (token_whitespace);
	else if (is_single_quote(line[*i]))
		return (token_quote);
	else if (is_double_quote(line[*i]))
		return (token_dquote);
	else if (is_operator(line[*i]))
		return (is_operator(line[*i]));
	else
		return (token_general);
}

static int			check_quotation_complete(char quote, char *line, int *i)
{
	(*i)++;
	while (line[*i] != quote && line[*i])
		(*i)++;
	if (line[*i] == quote)
		return(0);
	else
	{
		printf("[Multiple line command is not part of the subject\n]");
		exit(1);
	}	
}

static int		check_meta_and_quote(char *line, int *i)
{
	while (!is_metachar(line[*i]) && line[*i])
	{
		if (is_single_quote(line[*i]) || is_double_quote(line[*i]))
			check_quotation_complete(line[*i], line, i);
		(*i)++;
	}
	return (0);
}

// static int			*init_token()
// {
// 	int 	*token;
// 	// int 	i;
	
// 	token = (int *)malloc(sizeof(int) * 12);
// 	ft_bzero(token, 12 * sizeof(int));

// 	return (token);

// 	// i = 0;
// 	// while (i < 12)
// 	// {
// 	// 	printf("token str = [%d]\n", token[i]);
// 	// 	i++;
// 	// }
// }

static void			save_word(char *line, int *i, t_lexer **head)
{
	t_lexer		*tmp;
	char		*str;
	int 		start;
	int 		len;
	int			*token;

	start = *i;
	// token = init_token();
	check_meta_and_quote(line, i);
	len = *i - start;
	str = ft_substr(line, start, len);
	tmp = ll_new_node(str);
	ll_lstadd_back(head, tmp);
}

/*
** Later kijken of deze type herdefiniering nog nodig is (afhankelijk van parsing)
*/

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
	tmp = ll_new_node(str);
	ll_lstadd_back(head, tmp);
	(*i)++;
}

void				lexer(char *line)
{
	t_lexer		*head;
	t_lexer		*list;
	int 		type;
	int 		i;
	
	init_lexer();


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
	list = head;
	printf("EIND RESULTAAT:\n");
	while (list)
	{
		printf("node-str = [%s]\n", list->str);
		list = list->next;	
	}
/// END TESTER
}
