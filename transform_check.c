/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:33:18 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/03 18:07:37 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				count_node(t_lexer *head)
{
	int 				i;

	i = -1;							//builtin telt niet mee

	while (head)
	{
        if (head->token[token_general])
		    i++;
        if (head->token[token_redirection])
		    head = head->next;
        head = head->next;
	}
	return (i);
}

char           *trunc_quotes(t_lexer *list,char *str)
{
    int     len;
   // t_command **commandstr;
    char       *newstr;
    len = ft_strlen(str);
    
    len = len - 2;
	newstr= ft_substr(list->str, 1, len);
    return(newstr);
}

int         node_count(t_lexer *count_node, int i)
{
    while(count_node && count_node->token[token_general])
	{
		i++;
		count_node = count_node->next;
	}
    return(i);
}

int     check_token(char *str)
{   
    if(!ft_strcmp(str, ">"))
		return(token_redirection_greater);
	else if (!ft_strcmp(str, ">>"))
		return (token_redirection_dgreater);
    else if (!ft_strcmp(str, "<"))
		return(token_redirection_lesser);
    else
        return(0); 
}
