/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:33:18 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/11 10:20:48 by maran         ########   odam.nl         */
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

void 			close_and_save_array(t_command **tmp, char **array, int y)
{
	if (array)
		array[y]= 0;
	(*tmp)->array = array;
}

int 	        redirection(t_lexer **sort, t_command **tmp)
{
    while ((*sort)->token[token_redirection])
    {
        if ((*sort)->token[token_redirection_greater])
            output_fill(sort, tmp, token_redirection_greater);
        if ((*sort)->token[token_redirection_dgreater])
            output_fill(sort, tmp, token_redirection_dgreater);
        if ((*sort)->token[token_redirection_lesser])
            input_fill(sort,tmp);
        if ((*sort)->next)
            *sort = (*sort)->next;
        else
            return (1);
    }
    return (0);
}

int             general(t_lexer **sort, t_command **tmp, char **array, int *y)
{
    char 	*newstr;
    
    while (*sort && (*sort)->token[token_general])
	{
		if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
		{
			newstr = trunc_quotes((*sort)->str);
			array[*y] = newstr;
		}
		else
			array[*y] = (*sort)->str;
		(*y)++;
		if ((*sort)->next)
			*sort = (*sort)->next;
		else
            return (1);
	}
    return (0);
}
