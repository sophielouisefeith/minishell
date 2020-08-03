/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform_check.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:33:18 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/03 12:01:48 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int				count_node(t_lexer *head)
{
	t_lexer   *count_node;
	int 				i;

	i = -1;			//builtin telt niet mee
	count_node = head;
	while (count_node)
	{
        if (count_node->token[token_general])
		    i++;
        if (count_node->token[token_redirection])
		    count_node = count_node->next;
        count_node = count_node->next;
	}
    // printf("hoeveel ruimte malloced hij nu[%d]\n", i);
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
