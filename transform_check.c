/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:33:18 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/07/31 08:25:52 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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
