/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_builtin_again.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 17:31:13 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 20:25:37 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			free_if_dollar(t_dollar **dollar)
{
	if ((*dollar)->new_str1)
		free((*dollar)->new_str1);
	if ((*dollar)->parameter)
		free((*dollar)->parameter);
	if ((*dollar)->new_str2)
		free((*dollar)->new_str2);
	free(*dollar);
}

void			check_builtin_again(t_command **command, t_env *envb, int y)
{
	char *new_str;
	char *tmp;
	char *y_space;

	if ((*command)->builtin == builtin_no_com && \
	(*command)->array[y] != NULL && y == 0)
	{
		new_str = ft_strdup("");
		while ((*command)->array && (*command)->array[y])
		{
			y_space = ft_strjoin((*command)->array[y], " ");
			tmp = ft_strjoin(new_str, y_space);
			free(new_str);
			new_str = ft_strdup(tmp);
			free(y_space);
			free(tmp);
			y++;
		}
		if (new_str && new_str[0] != '$')
		{
			lexer_parser_executer(new_str, &envb);
			g_own_exit = 999;
			free(new_str);
		}
	}
}
