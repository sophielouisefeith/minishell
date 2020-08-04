/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/04 11:01:32 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command			*ll_new_node_command(void *content, int builtin, \
int pipe_after, int pipe_before, int sem)
{
	t_command		*new;
    int n;

    n = 0;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (0);
	new->array = content;
	new->builtin = builtin;
    if(pipe_after)
        new->pipe_after = pipe_after;
    // else
    //     new->pipe_after = NULL;
    if(pipe_before)
        new->pipe_before = pipe_before;
    if(sem)
        new->sem = sem;
	new->next = NULL;
   
    // while (new->array[n])
	// {
	// 	printf("node-str[%d] = [%s]\n", n, new->array[n]);
	// 	n++;
	// }
    // printf("node---pipe after[%d]\n", new->pipe_after);
    // printf("node---builtin[%d]\n", new->builtin);
    // printf("node---pipe before[%d]\n", new->pipe_before);
    // printf("node---sem[%d]\n", new->sem);
    
	return (new);
}

void			ll_lstadd_back_command(t_command **head, t_command *new)
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

static void	redirection(t_lexer *head)
{
        if ((head)->token[token_redirection_greater]||
			(head)->token[token_redirection_dgreater])
            output_fill(&head);
        if((head)->token[token_redirection_lesser])
            input_fill(&head);
}

int				transform(t_lexer **head, t_command **command, int count)
{
	char 		**array;
	char 		*newstr;
	int 		type_built;
	int 		num_nodes;
	int 		y;
	t_command 	*tmp;
	// int	        *builtin;			//gebruik je niet
    int         pipe_after;
    int         pipe_before;
    int         i;
    int         sem;
             
    pipe_before = 0;         
    pipe_after =0;
    sem = 0;
    if(count == 1)
    {
        pipe_before = 1;
        i = 0;
    }
	// builtin = intspace(8);			//gebruik je niet.
	y = 0;
	num_nodes = count_node(*head);
	array = (char **)malloc((num_nodes + 1) * sizeof(char *));
	if (array == NULL)
		printf("Malloc failed\n"); 		// error functie van maken 
	type_built = check_builtin_node(head);
	while((*head && ((*head)->token[token_general] || (*head)->token[token_redirection])))
	{
        if ((*head)->token[token_redirection])
		{
			redirection(*head);
			if ((*head)->next)
            	*head = (*head)->next;
			else
				break ;
		}
		if ((*head)->token[token_quote] || (*head)->token[token_dquote])
		{
			newstr = trunc_quotes(*head, (*head)->str);
			array[y] = newstr;
		}
		else
			array[y] = (*head)->str;
		y++;
		*head = (*head)->next;
	}
	if(array)
		array[y]= 0;
	// tmp = ll_new_node_command(array, type_built, pipe_after, pipe_before);
	//ll_lstadd_back_command(&command, tmp);
    if(*head && (*head)->token[token_semicolon])
        sem = 1;
    if(*head && (*head)->token[token_pipe] && !count)
    {
        pipe_after = 1;
        tmp = ll_new_node_command(array, type_built, pipe_after, pipe_before, sem);
        // tmp->pipe_after = 1;
        ll_lstadd_back_command(command, tmp);
       // tmp = ll_new_node_command(&pipe_after, type_built);
       // printf("echo hallo[%s]",tmp);
       // ll_lstadd_back_command(&command, tmp);
        return(1);
    }
    tmp = ll_new_node_command(array, type_built, pipe_after, pipe_before, sem);
    ll_lstadd_back_command(command, tmp);
    // tester_pars(*head, command);
    return(i);
}