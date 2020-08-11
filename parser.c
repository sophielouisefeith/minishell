/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/11 17:10:38 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command			*ll_new_node_command()
{
	t_command		*new;

	new = (t_command *)malloc(sizeof(t_command));
	if(!new)
		error_free(12);
	new->array = NULL;
	new->builtin = 0;
   	new->pipe_after = 0;
	new->pipe_before = 0;
	new->sem = 0;
	new->next = NULL;
	return (new);
}

static void			        ll_lstadd_back_command(t_command **head, t_command *new)
{
	t_command		*list;
	void			*del;

	list = *head;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*head = new;
	free_list_command(head, del);
}

static void			check_operator(t_lexer **sort, t_command **tmp, char **array)
{
	int		ret;
    int 	y;

    y = 0;
	while (*sort && ((*sort)->token[token_general]
				|| (*sort)->token[token_redirection]))
	{
		ret = redirection(sort, tmp);
		if (ret == 1)
			return (close_and_save_array(tmp, array, y));
		ret = general(sort, tmp, array, &y);
		if (ret == 1)
			return (close_and_save_array(tmp, array, y));
	}
	return (close_and_save_array(tmp, array, y));
}

static int            fill_node_parsing(t_lexer **head, t_command **command, int count, t_command **tmp)
{
    int         i;
	void        *del;	

    if (count == 1)
    {
        (*tmp)->pipe_before = 1;
        i = 0;
    }
    if (*head && (*head)->token[token_semicolon])
        (*tmp)->sem = 1;
    if (*head && (*head)->token[token_pipe] && !count)
    {
        (*tmp)->pipe_after = 1;
        ll_lstadd_back_command(command, *tmp);
        return (1);
	}
    ll_lstadd_back_command(command, *tmp);
    return (i);
}

int				parser(t_lexer **sort, t_command **command, int count)
{
	char 		**array;
	int 		num_nodes;
	t_command 	*tmp;

	tmp = NULL;
	tmp = ll_new_node_command();
	num_nodes = count_node(*sort);
	//error_free(12);
	array = (char **)malloc((num_nodes + 1) * sizeof(char *));
	//array = NULL;
	if (array == NULL)
		error_free(12);
	tmp->builtin = check_builtin_node(sort);
    check_operator(sort, &tmp, array);
    return (fill_node_parsing(sort, command, count, &tmp));
}
