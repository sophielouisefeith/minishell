/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:33:18 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/13 10:33:06 by maran         ########   odam.nl         */
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

char            *trunc_quotes(char *str)
{
    int     len;
    char     *newstr;
    
    len = ft_strlen(str);
    len = len - 2;
	newstr = ft_substr(str, 1, len);
    return (newstr);
}


int				get_builtin_type(char *str)
{   
    if (!ft_strcmp(str, "echo"))
		return (builtin_echo);
	else if (!ft_strcmp(str, "cd"))
		return (builtin_cd);
    else if (!ft_strcmp(str, "pwd"))
		return (builtin_pwd);
	else if (!ft_strcmp(str, "export"))
		return (builtin_export);
    else if (!ft_strcmp(str, "unset"))
		return (builtin_unset);
	else if (!ft_strcmp(str, "env"))
		return (builtin_env);
   else if (!ft_strcmp(str, "exit"))
		return (builtin_exit); 
    else
        return (builtin_no);
}

/*
** Removes quotation and returns builtin_type
*/

int				check_builtin_node(t_lexer **sort)
{
	char 	*newstr;
	int 	builtin_type;

    if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
	    newstr = trunc_quotes((*sort)->str);
    else
        newstr = (*sort)->str;
	builtin_type = get_builtin_type(newstr);
	*sort = (*sort)->next;
	return (builtin_type);
}
