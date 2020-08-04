/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 11:53:32 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/04 10:21:20 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int         get_builtin_type(char *str)
{   
    if(!ft_strcmp(str, "echo"))
		return(builtin_echo);
	else if (!ft_strcmp(str, "cd"))
		return (builtin_cd);
    else if (!ft_strcmp(str, "pwd"))
		return(builtin_pwd);
	else if (!ft_strcmp(str, "export"))
		return(builtin_export);
    else if (!ft_strcmp(str, "unset"))
		return(builtin_unset);
	else if (!ft_strcmp(str, "env"))
		return(builtin_env);
   else if (!ft_strcmp(str, "exit"))
		return(builtin_exit); 
    else
        return(builtin_no);
}

int			check_builtin_node(t_lexer **head)
{
	char *newstr;
	int type_built;

    if((*head)->token[token_quote] || (*head)->token[token_dquote])
	    newstr = trunc_quotes(*head, (*head)->str);
    else
        newstr = (*head)->str;
	type_built = get_builtin_type(newstr);
	*head = (*head)->next;
	return (type_built);
}