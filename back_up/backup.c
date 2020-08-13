/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   backup.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/21 12:05:45 by maran         #+#    #+#                 */
/*   Updated: 2020/07/21 13:26:57 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */



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
		if (!is_whitespace(line[*i + 1]) && !is_operator(line[*i + 1]))					// check of teken na " een splitting char is (white space of opertar)
		{
			if (is_single_quote(line[*i + 1]) || is_double_quote(line[*i + 1]))			//Geen splitting, check of het een " " is
			{
				while (line[start] != line[*i] && line[*i])								//Check of " " compleet is
					(*i)++;
			}	
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


// enum	token_type{
// 	token_general = -1,
// 	token_null = '\0', 
// 	token_whitespace = ' ',
// 	token_quote = '\'',
// 	token_dquote = '\"', 
// 	token_newline = '\n',
// 	token_tab = '\t', 
// 	token_char_pipe = '|',
// 	token_semicolon = ';',
// 	token_redirection_greater = '>',
// 	token_redirection_lesser = '<',
// 	token_dollar = '$',
// };