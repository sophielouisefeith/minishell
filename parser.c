/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/10/30 20:05:24 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void 	close_and_save_array(t_command **tmp, char **array, int y)
{
	//printf("close&safearray--------parser\n");
	if (array != NULL)
		array[y]= 0;
	(*tmp)->array = array;
}

static int		redirection(t_lexer **sort, t_command **tmp)
{
	//printf("redirectins--------parser\n");
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
	//printf("-------------general_parser\n");
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

static void		fill_builtin_redirec_array(t_lexer **sort, t_command **tmp, t_env **_env)
{
	//printf("fill_builtin_redirec_array--------parser\n");
	char 		**array;
	int 		*quote;
	int 		num_nodes;
	int			ret;
    int 		y;

	array = NULL;
	quote = NULL;
	num_nodes = 0;
	y = 0;
	(*tmp)->builtin = check_builtin_node(sort, _env);
	num_nodes = count_node(sort, (*tmp)->builtin);
	if (num_nodes > 0)
	{
		array = (char **)malloc((num_nodes + 1) * sizeof(char *));
		if (array == NULL)
			malloc_fail();
	}
	while (*sort && ((*sort)->token[token_general]
				|| (*sort)->token[token_redirection]))
	{
		ret = redirection(sort, tmp);
		if (ret == 1)
			return (close_and_save_array(tmp, array, y));
		ret = general(sort, array, &y);
		if (ret == 1)
			return (close_and_save_array(tmp, array, y));
	}
	return (close_and_save_array(tmp, array, y));
}

/*
** Pipe_status == 1 --> Pipe_before
*/

int				parser(t_lexer **sort, t_command **command, int pipe_status,
							t_env **_env)
{
	//printf("parser\n");
	t_command 	*tmp;

	g_own_exit = 0;
	tmp = NULL;
	tmp = ll_new_node_command();
	if (tmp == NULL)
		return (malloc_fail());
    fill_builtin_redirec_array(sort, &tmp, _env);
	if (g_own_exit == 258)
		return (3);   //hier exit status checken 
	if (*sort && (*sort)->token[token_semicolon])
    	(tmp)->sem = 1;
    if (pipe_status == 1)
	{
		(tmp)->pipe_before = 1;
		pipe_status = 0;
	}
	if (*sort && (*sort)->token[token_pipe])
    {
		(tmp)->pipe_after = 1;
		pipe_status = 1;
	}
	ll_lstadd_back_command(command, tmp);
	return (pipe_status);
}
