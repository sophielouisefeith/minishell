/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/04 11:52:36 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_command			*ll_new_node_command(void *content, int builtin, \
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
    if(pipe_before)
        new->pipe_before = pipe_before;
    if(sem)
        new->sem = sem;
    while (new->array[n])
	{
		printf("node-str[%d] = [%s]\n", n, new->array[n]);
		n++;
	}
    printf("node---pipe after[%d]\n", new->pipe_after);
    printf("node---builtin[%d]\n", new->builtin);
    printf("node---pipe before[%d]\n", new->pipe_before);
    printf("node---sem[%d]\n", new->sem);
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

static void                 check_operator(t_lexer **head, char *newstr, char **array)
{
    int y;

    y = 0;
    while((*head && ((*head)->token[token_general] || (*head)->token[token_redirection])))
	{
        if ((*head)->token[token_redirection])
		{
			redirection(*head);                         //hier vullen we input & output
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
}

static int            fill_node_parsing(t_lexer **head, t_command *command,int count, \
char **array, int type_built)
{
    int         pipe_after;
    int         pipe_before;
    int         i;
    int         sem;
    //t_command 	*command; 				//command head
	t_command 	*tmp;
    
    //command = NULL;         
    pipe_before = 0;         
    pipe_after =0;
    sem = 0;
    if(count == 1)
    {
        pipe_before = 1;
        i = 0;
    }
    if(*head && (*head)->token[token_semicolon])
        sem = 1;
    if(*head && (*head)->token[token_pipe] && !count)
    {
        pipe_after = 1;
        tmp = ll_new_node_command(array, type_built, pipe_after, pipe_before, sem);
        ll_lstadd_back_command(&command, tmp);
        return(1);
    }
    tmp = ll_new_node_command(array, type_built, pipe_after, pipe_before, sem);
    ll_lstadd_back_command(&command, tmp);
    return(i);
}

int				transform(t_lexer **head, t_command **command, int count)
{
	char 		**array;
	char 		*newstr;
	int 		type_built;
	int 		num_nodes;
             

	num_nodes = count_node(*head);
	array = (char **)malloc((num_nodes + 1) * sizeof(char *));
	if (array == NULL)
		printf("Malloc failed\n"); 		// error functie van maken 
	type_built = check_builtin_node(head);
    check_operator(head, newstr, array);
    return(fill_node_parsing(head, *command,count, array, type_built));

}
