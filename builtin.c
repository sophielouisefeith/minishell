/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 11:53:32 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/10 16:46:00 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
