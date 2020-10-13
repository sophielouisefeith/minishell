/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 14:33:18 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/10/09 17:20:40 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Counts number of general nodes
** Changelog 08/09:
	- Count_node aangepast zodat we van ? af zijn in fill_builtin_redirec_array
	- Big changes in check_builtin_node: quotes veel korter (gaat dit goed?), check_path toevoeging.
*/

int				count_node(t_lexer *sort, int type_builtin)
{
	int 	i;

	i = 0;
	while (sort && !sort->token[token_pipe] && !sort->token[token_semicolon])
	{
        if (sort->token[token_general])
		    i++;
        if (sort->token[token_redirection])
		    sort = sort->next_sort;
        sort = sort->next_sort;
	}
	if (type_builtin >= builtin_echo && type_builtin <= builtin_exit)
		i--;
	// printf("i = %d \n", i);
	return (i);
}

/*
** Changelog:
	- Added 29/09(na vak):
	free(str);				//freet dit de (*sort)->str) goed?
*/

char            *trunc_quotes(char *str)
{
    int     len;
    char     *newstr;

    len = ft_strlen(str);
    len = len - 2;
	newstr = ft_substr(str, 1, len);
	free(str);
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
	else if (!ft_strncmp(str, "/", 1) || !ft_strncmp(str, "./", 2)) 			// New (na vak)
		return (executable);
	else
		return (builtin_no);
}

/* Waarom hadden we eerst:
if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
	{
		newstr = trunc_quotes((*sort)->str);
		builtin_type = get_builtin_type(newstr);
		printf("(*sort)->str = [%s]\n", (*sort)->str);
		free (newstr);
		return (builtin_type);
	}
	--> Waarom niet direct sort->str ontdoen van quotes? Hier was vast een reden voor.
** TO DO:
	- We moeten nu 2x quotes truncen (general en hieronder). Kunnen we structuur aanpassen zodat dit maar 1x hoeft?
*/

/*
"\echo" hallo
bash: \echo: command not found

echohallo: command not found
"echo"hallo


*/


char		*delete_quotes(char *src, char garbage)
{
	char *dst;
	int dst_i;
	int src_i;
	int len;
	int count;

	src_i = 0;
	dst_i = 0;
	count = 0;
	len = ft_strlen(src) - 2;
	dst = (char *)malloc(sizeof(char) * (len + 1));			//New: gaat dit goed, moet ik wel opnieuw mallocen. Let op bij freeen. 
	while (src[src_i] != '\0')
	{
		if (src[src_i] == garbage && count < 2)
		{
			src_i++;
			count++;
		}
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
    dst[len] = '\0';
	return (dst);
}

	// printf("(*sort)->str = [%s]\n", (*sort)->str);
/*
** Check path checks the env variable path for commands, and completes the path.
** For example "ls" --> "/bin/ls".
** If there is no match the builtin type will be set to builtin_no_com. If there is a match
** it stays "builtin_no".
*/

		// printf("(*sort)->str = [%s]\n", (*sort)->str);

int				check_builtin_node(t_lexer **sort, t_env **_env, t_command **tmp)
{
	int 	builtin_type;
	char 	*str_before;

	
	if (is_single_quote((*sort)->str[0]) || is_double_quote((*sort)->str[0]))		//mag alleen bij het eerste woord worden getrunct (hoezo komt hij niet bij volgende woorden?)
		(*sort)->str = delete_quotes((*sort)->str, (*sort)->str[0]);
	builtin_type = get_builtin_type((*sort)->str);
	if (builtin_type == builtin_no)
	{
		//printf("------je bent geen builtin\n");
		str_before = (*sort)->str;
		(*sort)->str = check_path(*_env, (*sort)->str);
		if (!ft_strcmp(str_before, (*sort)->str))
			builtin_type = builtin_no_com;
	}
	return (builtin_type);
}


//OLD

// int				count_node(t_lexer *sort)
// {
// 	int 	i;

// 	i = -1;
// 	while (sort && !sort->token[token_pipe] && !sort->token[token_semicolon])
// 	{
//         if (sort->token[token_general])
// 		    i++;
//         if (sort->token[token_redirection])
// 		    sort = sort->next_sort;
//         sort = sort->next_sort;
// 	}
// 	return (i);
// }

	// printf("(*sort)->str = [%s]\n", (*sort)->str);

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

// int				check_builtin_node(t_lexer **sort, t_env **_env, t_command **tmp)
// {
// 	char 	*newstr;
// 	int 	builtin_type;
// 	char *str_before;

//     if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
// 	{
// 		newstr = trunc_quotes((*sort)->str);
// 		builtin_type = get_builtin_type(newstr);
// ///																			//new
// 		if (builtin_type == 0)
// 		{
// 			(*sort)->str = check_path(*_env, (*sort)->str);
// 			return (builtin_type);											//ga niet naar de volgende node
// 		}
// ///
// 		free (newstr);
// 		// *sort = (*sort)->next_sort;
// 		return (builtin_type);
// 	}
// 	else
// 		newstr = (*sort)->str;
// 	builtin_type = get_builtin_type(newstr);
// ///	
// 																		//new
// 	if (builtin_type == builtin_no)
// 	{
// 		str_before = (*sort)->str;
// 		(*sort)->str = check_path(*_env, (*sort)->str);
// 		if (!ft_strcmp(str_before, (*sort)->str))
// 			builtin_type = builtin_no_com;
// 		return (builtin_type);											//ga niet naar de volgende node
// 	}
// ///
// 	// *sort = (*sort)->next_sort;
// 	return (builtin_type);
// }
