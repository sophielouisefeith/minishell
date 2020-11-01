/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/11/01 10:36:29 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		redirection(t_lexer **sort, t_command **tmp)
{
	while ((*sort)->token[token_redirection])
	{
		if ((*sort)->token[token_redirection_greater])
			output_fill(sort, tmp, token_redirection_greater);
		if ((*sort)->token[token_redirection_dgreater])
			output_fill(sort, tmp, token_redirection_dgreater);
		if ((*sort)->token[token_redirection_lesser])
			input_fill(sort,tmp);
		if ((*sort)->next_sort)
			*sort = (*sort)->next_sort;
		else
			return (1);
	}
	return (0);
}

static int		general(t_lexer **sort, char **array, int *y)
{
	while (*sort && (*sort)->token[token_general])
	{
		array[*y] = ft_strdup((*sort)->str);
		if (array[*y] == NULL)
			malloc_fail();
		(*y)++;
		if ((*sort)->next_sort)
			*sort = (*sort)->next_sort;
		else
			return (1);
	}
	return (0);
}

static void		fill_pipe_and_sem(t_lexer *sort, \
t_command **tmp, int *pipe_status)
{
	if (sort && sort->token[token_semicolon])
		(*tmp)->sem = 1;
	if (*pipe_status == 1)
	{
		(*tmp)->pipe_before = 1;
		*pipe_status = 0;
	}
	if (sort && sort->token[token_pipe])
	{
		(*tmp)->pipe_after = 1;
		*pipe_status = 1;
	}
}

static void		fill_array(t_lexer **sort, t_command **tmp)
{
	int			ret;
	int 		y;

	y = 0;
	while (*sort && ((*sort)->token[token_general]
				|| (*sort)->token[token_redirection]))
	{
		ret = redirection(sort, tmp);
		if (ret == 1)
			break ;
		ret = general(sort, (*tmp)->array, &y);
		if (ret == 1)
			break ;
	}
	if ((*tmp)->array != NULL)
		(*tmp)->array[y] = 0;
}

/*
** Pipe_status == 1 --> Pipe_before
*/

int				parser(t_lexer **sort, t_command **command, int pipe_status)
{
	t_command	*tmp;
	int			num_nodes;
	int			builtin;

	g_own_exit = 0;									//M: Is dit voor de error-afhandeling?
	tmp = NULL;
	num_nodes = 0;
	builtin = check_builtin_node(sort);
	num_nodes = count_node(sort, builtin);
	tmp = ll_new_node_command(num_nodes, builtin);
	if (tmp == NULL)
		return (malloc_fail());
	fill_array(sort, &tmp);
	if (g_own_exit == 258)							//M: vragen aan Sop
		return (3);									//hier exit status checken dit is dat hij 
	fill_pipe_and_sem(*sort, &tmp, &pipe_status);
	ll_lstadd_back_command(command, tmp);
	return (pipe_status);
}
