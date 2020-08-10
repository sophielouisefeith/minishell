/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:33:18 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/10 16:36:58 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Counts number of general nodes
** To do:
** - Testen of het in alle gevallen goed gaat door op -1 te beginnen.
*/

int				count_node(t_lexer *sort)
{
	int 	i;

	i = -1;
	while (sort && !sort->token[token_pipe] && !sort->token[token_semicolon])
	{
        if (sort->token[token_general])
		    i++;
        if (sort->token[token_redirection])
		    sort = sort->next;
        sort = sort->next;
	}
	return (i);
}

/*
** Changelog:
    - Removed:
    t_lexer *sort
*/

char            *trunc_quotes(char *str)
{
    int     len;
    char    *newstr;
    
    len = ft_strlen(str);
    len = len - 2;
	newstr = ft_substr(str, 1, len);
    return (newstr);
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

void 	        redirection(t_lexer **head, t_command **tmp)
{
        if ((*head)->token[token_redirection_greater]||
			(*head)->token[token_redirection_dgreater])
            output_fill(head, tmp);
        if((*head)->token[token_redirection_lesser])
            input_fill(head,tmp);
}