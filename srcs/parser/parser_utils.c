/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser_utils.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/01 18:00:44 by msiemons      #+#    #+#                 */
/*   Updated: 2020/11/05 17:33:00 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				count_node(t_lexer **sort, int type_builtin)
{
	t_lexer		*list;
	int			i;

	i = 0;
	list = *sort;
	while (list && !list->token[token_pipe] && !list->token[token_semicolon])
	{
		if (list->token[token_general])
			i++;
		if (list->token[token_redirection])
			list = list->next_sort;
		list = list->next_sort;
	}
	if (type_builtin >= builtin_echo && type_builtin <= builtin_exit)
	{
		i--;
		*sort = (*sort)->next_sort;
	}
	return (i);
}

static int		return_type_and_free(char **tmp, int type)
{
	free(*tmp);
	*tmp = NULL;
	return (type);
}

int				get_builtin_type(char *str)
{
	char		*tmp;

	tmp = NULL;
	tmp = tmp_tolower(str);
	if (!ft_strcmp(tmp, "echo"))
		return (return_type_and_free(&tmp, builtin_echo));
	else if (!ft_strcmp(tmp, "cd"))
		return (return_type_and_free(&tmp, builtin_cd));
	else if (!ft_strcmp(tmp, "pwd"))
		return (return_type_and_free(&tmp, builtin_pwd));
	else if (!ft_strcmp(tmp, "export"))
		return (return_type_and_free(&tmp, builtin_export));
	else if (!ft_strcmp(tmp, "unset"))
		return (return_type_and_free(&tmp, builtin_unset));
	else if (!ft_strcmp(tmp, "env"))
		return (return_type_and_free(&tmp, builtin_env));
	else if (!ft_strcmp(tmp, "exit"))
		return (return_type_and_free(&tmp, builtin_exit));
	else if (ft_strchr(tmp, '/'))
		return (return_type_and_free(&tmp, executable));
	else
		return (return_type_and_free(&tmp, builtin_no));
}

char			*delete_quotes(char *src, char garbage)
{
	char		*dst;
	int			dst_i;
	int			src_i;
	int			count;

	src_i = 0;
	dst_i = 0;
	count = 0;
	dst = (char *)calloc(((ft_strlen(src) - 2) + 1), sizeof(char));
	while (src[src_i] != '\0')
	{
		if (src[src_i] == garbage && count < 2)
		{
			src_i++;
			count++;
			if (!src[src_i])
				break ;
		}
		dst[dst_i] = src[src_i];
		src_i++;
		dst_i++;
	}
	dst[dst_i] = '\0';
	return_type_and_free(&src, 0);
	return (dst);
}

int				check_builtin_node(t_lexer **sort)
{
	int			builtin_type;
	char		*tmp;

	tmp = NULL;
	if (is_single_quote((*sort)->str[0]) || is_double_quote((*sort)->str[0]))
	{
		tmp = strdup_and_free(&(*sort)->str);
		(*sort)->str = delete_quotes(tmp, tmp[0]);
	}
	builtin_type = get_builtin_type((*sort)->str);
	if (builtin_type == builtin_no && (*sort)->str[0] == ';')
	{
		error_command(";", 0, 0);
		g_own_exit = 258;
	}
	return (builtin_type);
}
