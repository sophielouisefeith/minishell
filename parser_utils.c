/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:33:18 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/09/08 14:48:25 by SophieLouis   ########   odam.nl         */
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
		    sort = sort->next_sort;
        sort = sort->next_sort;
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
**
** Changelog:
	- Bij if toegevoegd:
		builtin_type = get_builtin_type(newstr);
		free (newstr);									--> vanwege deze
		*sort = (*sort)->next_sort;
		return (builtin_type);
** TO DO:
	- Kan dit mooier deze toevoeging?
*/

int				check_builtin_node(t_lexer **sort, t_env **_env, t_command **tmp)
{
	char 	*newstr;
	int 	builtin_type;

    if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
	{
		newstr = trunc_quotes((*sort)->str);
		builtin_type = get_builtin_type(newstr);
///																			//new
		if (builtin_type == 0)
		{
			(*sort)->str = check_path(*_env, (*sort)->str);
			return (builtin_type);											//ga niet naar de volgende node
		}
///
		free (newstr);
		*sort = (*sort)->next_sort;
		return (builtin_type);
	}
	else
		newstr = (*sort)->str;
	builtin_type = get_builtin_type(newstr);
///																			//new
	if (builtin_type == 0)
	{
		printf("------------VOOR -----------\n");
		(*sort)->str = check_path(*_env, (*sort)->str);
		printf("------------NA -----------\n");
		// printf("str[%s]\n", (*sort)->str);
		
		return (builtin_type);												//ga niet naar de volgende node
	}
///
	*sort = (*sort)->next_sort;
	return (builtin_type);
}
