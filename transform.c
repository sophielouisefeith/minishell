/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/03 15:22:59 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command			*ll_new_node_command(void *content, int builtin)
{
	t_command		*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (0);
	new->array = content;
	new->builtin = builtin;
	new->next = NULL;
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
        if ((head)->token[7]|| (head)->token[9])
            output_fill(&head);
        if((head)->token[8])
            input_fill(&head);
}


int				transform(t_lexer **head, int count)
{
	char 		**array;
	char 		*newstr;
	int 		type_built;
	int 		num_nodes;
	int 		y;
	t_command 	*command; //command head
	t_command 	*tmp;
	int	        *builtin;
    int         pipe_after;
    int         pipe_before;
    int         i;

    printf("komt binnen in transform: head->str [%s]\n", ((*head)->str));
    if(count == 1)
    {
        pipe_before = 1;
        pipe_after = 0;
        i = 0;
    }
	builtin = intspace(8);
	y = 0;
	command = NULL;
	num_nodes = count_node(head);
	array = (char **)malloc((num_nodes + 1) * sizeof(char *));
	if (array == NULL)
		printf("Malloc failed\n"); // error functie van maken 
	type_built = check_builtin_node(head);
	while((head && ((*head)->token[token_general] || (*head)->token[token_redirection])))
	{
        printf("In while loop: head->str [%s]\n", ((*head)->str));
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
	tmp = ll_new_node_command(array, type_built);
	ll_lstadd_back_command(&command, tmp);
    if(head && (*head)->token[token_pipe] && !count)
    {
        pipe_after = 1;
        return(1);
    }
    return(i);
    
    
   


//// Tester
// 		2d array printer:
	// y = 0;
	// while(array[y])
	// {
	// 	printf("dubbel array[%s]\n", array[y]);
	// 	y++;
	// }
//Linked list 2d array printer
	// t_command		*list;
	// int n;
	
	// n = 0;
	// list = command;
	// printf("EIND RESULTAAT TRANSFORM:\n");
	// printf("node-builtin = [%d]\n", list->builtin);
	// while (list->array[n])
	// {
	// 	printf("node-str[%d] = [%s]\n", n, list->array[n]);
	// 	n++;
	// }
//// Einde Tester
}