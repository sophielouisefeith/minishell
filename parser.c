/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/17 12:25:39 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Changelog:
	//changed next to  next_sort
*/

static void 	close_and_save_array(t_command **tmp, char **array, int y)
{
	if (array != NULL)
		array[y]= 0;
	(*tmp)->array = array;
}

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

/*
** Changelog:
	- Toegevoegd:
	free(newstr);
	newstr = NULL;
	- Removed:
	free(newstr);
	newstr = NULL;
	- Changed:
	array[*y] = (*sort)->str;
*/

static int		general(t_lexer **sort, char **array, int *y)
{
    char		*newstr;

    
    while (*sort && (*sort)->token[token_general])
	{
		if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
		{
			newstr = trunc_quotes((*sort)->str);
			array[*y] = newstr;
		}
		else
			array[*y] = ft_strdup((*sort)->str);				//new
		(*y)++;
		if ((*sort)->next_sort)
			*sort = (*sort)->next_sort;
		else
            return (1);
	}
    return (0);
}

/*
** Changelog:
	- toegevoegd:
	if (num_nodes > 0)
*/

static void		fill_builtin_redirec_array(t_lexer **sort, t_command **tmp)
{
	char 		**array;
	int 		num_nodes;
	int			ret;
    int 		y;

	array = NULL;
	num_nodes = 0;
	y = 0;
	num_nodes = count_node(*sort);
	if (num_nodes > 0)
		array = (char **)malloc((num_nodes + 1) * sizeof(char *));
	// if (array == NULL)
	// 	error_free(12);
	(*tmp)->builtin = check_builtin_node(sort);
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
** Changelog:
	- Veel gereorganiseerd, check github < 13-08-2020 voor versie hiervoor.
*/

int				parser(t_lexer **sort, t_command **command, int pipe_status)
{
	t_command 	*tmp;

	tmp = NULL;
	tmp = ll_new_node_command();
    fill_builtin_redirec_array(sort, &tmp);
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
