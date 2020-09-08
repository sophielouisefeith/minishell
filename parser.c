/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/09/08 16:40:48 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void 	close_and_save_array(t_command **tmp, char **array, int y, int *quote)
{
	printf("------------close and save array----------\n");
	if (array != NULL)
		array[y]= 0;
	(*tmp)->array = array;
	(*tmp)->quote = quote;
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
	- Changed:
	array[*y] = (*sort)->str;
*/

static int		general(t_lexer **sort, char **array, int *y, int *quote)
{
    char		*newstr;

    while (*sort && (*sort)->token[token_general])
	{
		if ((*sort)->token[token_quote] || (*sort)->token[token_dquote])
		{
			newstr = trunc_quotes((*sort)->str);
			array[*y] = newstr;
			quote[*y] = ((*sort)->token[token_quote]) ? token_quote : token_dquote;			//new
		}
		else
			array[*y] = ft_strdup((*sort)->str);
		(*y)++;
		if ((*sort)->next_sort)
			*sort = (*sort)->next_sort;
		else
            return (1);
	}
    return (0);
}

/*
** TO DO:
	- Door het moeten toevoegen van quote wordt de functie te groot. Is dit de beste plek?
*/

static void		fill_builtin_redirec_array(t_lexer **sort, t_command **tmp, t_env **_env)
{
	char 		**array;
	int 		*quote;
	int 		num_nodes;
	int			ret;
    int 		y;

	array = NULL;
	quote = NULL;
	num_nodes = 0;
	y = 0;
	num_nodes = count_node(*sort);
	(*tmp)->builtin = check_builtin_node(sort, _env, tmp);
	num_nodes = ((*tmp)->builtin == 0) ? (num_nodes + 1) : num_nodes;			//new	//in count_nodes fixen?
	if (num_nodes > 0)
	{
		array = (char **)malloc((num_nodes + 1) * sizeof(char *));
		// if (array == NULL)
		// 	error_free(12);
		quote = allocate_memory_int_string(num_nodes);							//new
	}
	while (*sort && ((*sort)->token[token_general]
				|| (*sort)->token[token_redirection]))
	{
		ret = redirection(sort, tmp);
		if (ret == 1)
			return (close_and_save_array(tmp, array, y, quote));
		ret = general(sort, array, &y, quote);
		if (ret == 1)
			return (close_and_save_array(tmp, array, y, quote));
	}
	return (close_and_save_array(tmp, array, y, quote));
}

/*
** Pipe_status == 1 --> Pipe_before
** Changelog:
	- Veel gereorganiseerd, check github < 13-08-2020 voor versie hiervoor.
*/

int				parser(t_lexer **sort, t_command **command, int pipe_status, t_env **_env)
{
	t_command 	*tmp;

	tmp = NULL;
	tmp = ll_new_node_command();
    fill_builtin_redirec_array(sort, &tmp, _env);
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
