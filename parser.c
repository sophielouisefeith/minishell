/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/10 14:54:07 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command			*ll_new_node_command()
{
	t_command		*new;

	new = (t_command *)malloc(sizeof(t_command));
	//if(!new)
		//error_free(errno);
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

	list = *head;
	if (list)
	{
		while (list->next)
			list = list->next;
		list->next = new;
	}
	else
		*head = new;
}

static void                 check_operator(t_lexer **head, t_command **tmp, char **array)
{
	char 		*newstr;
    int 		y;

    y = 0;
	while (*head && ((*head)->token[token_general] || (*head)->token[token_redirection]))
	{
		while ((*head)->token[token_redirection])
		{
			redirection(head, tmp);
			if ((*head)->next)
            	*head = (*head)->next;
			else
			{
				if (array)
					array[y]= 0;
				(*tmp)->array = array;
				return ;
			}
		}
		while(*head && (*head)->token[token_general])
		{
			if ((*head)->token[token_quote] || (*head)->token[token_dquote])
			{
				newstr = trunc_quotes(*head, (*head)->str);
				array[y] = newstr;
			}
			else
			{
				array[y] = (*head)->str;
			}
			y++;
			if ((*head)->next)
				*head = (*head)->next;
			else
			{
				if (array)
					array[y]= 0;
				(*tmp)->array = array;
				return ;
			}
		}
	}
	if (array)
		array[y]= 0;
	(*tmp)->array = array;
	return ;
}

static int            fill_node_parsing(t_lexer **head, t_command **command, int count, t_command **tmp)
{
    int         i;

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
	array = (char **)malloc((num_nodes + 1) * sizeof(char *));
	//if (array == NULL)
		//error_free(errno);
	tmp->builtin = check_builtin_node(sort);
    check_operator(sort, &tmp, array);
    return (fill_node_parsing(sort, command, count, &tmp));
}
