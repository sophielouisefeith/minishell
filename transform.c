/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/01 17:40:38 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				count_node(t_lexer *head)
{
	t_lexer   *count_node;
	int 				i;

	i = -1;			//builtin telt niet mee
	count_node = head;
	while(count_node)
	{
        if(count_node->token[token_general])
		    i++;
        if(count_node->token[token_redirection])
		    count_node = count_node->next;
        count_node = count_node->next;
	}
    printf("hoeveel ruimte malloced hij nu[%d]\n", i);
	return (i);
}



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

static void	redirection(t_lexer **head)
{
	
    // while (head)                                         //dit moet dus veranderd naar output_head
    // {
        if ((*head)->token[7]|| (*head)->token[9])
            output_fill(head);
        // head = head->next;
        if((*head)->token[8])
            input_fill(head);
        // head = head->next;
    
}

static int		fill_operator(t_lexer *head)
{
	t_command command;
	int pipe_after;
	int sem_after;
	
	if(head && head->token[token_pipe])
		return(pipe_after = 1);
	if(head && head->token[token_semicolon])
		return(sem_after = 1);
	return(0);
}

static void			command_next(t_command *command, t_lexer *head)
{
	int		pipe_after;
	int		pipe_before;
	int		sem_after;
	int		sem_before;
	
	if(pipe_after == 1 && command)
	{
		pipe_after = 0; 
		command = command->next;
		pipe_before = 1;
	}
	if(sem_after == 1 && command)
	{
        sem_after = 0; 
		command = command->next;
		sem_before = 1;
	}
	command = command->next;
}

void				transform(t_lexer *head)
{
	char 		**array;
	char 		*newstr;
	int 		type_built;
	int 		num_nodes;
	int 		y;
	t_command 	*command; //command head
	t_command 	*tmp;


	int	 *builtin;

	builtin = intspace(8);
	y = 0;
	command = NULL;
	num_nodes = count_node(head);
	printf("num nodes = %d \n", num_nodes);
	
	array = (char **)malloc((num_nodes + 1) * sizeof(char *));
	if (array == NULL)
		printf("Malloc failed\n");
	type_built = check_builtin_node(&head);

	while((head && (head->token[token_general] || head->token[token_redirection])))
	{
        if (head->token[token_redirection])
		{
			redirection(&head);
			if (head->next)
            	head = head->next;
			else
				break ;
		}
		if (head->token[token_quote] || head->token[token_dquote])
		{
			newstr = trunc_quotes(head, head->str);
			array[y] = newstr;
		}
		else
			array[y] = head->str;
		y++;
		head = head->next;
	}
	if(array)
		array[y]= 0;
	if(head && (head->token[7] || head->token[8] || head->token[9]))
		redirection(&head);
	tmp = ll_new_node_command(array, type_built);
	ll_lstadd_back_command(&command, tmp);
    // hier komt een functie die de parsing nog een keer oproept en kijkt naar ervoor en erna
	// fill_operator(head);
	// command_next(command, head);
	//transform(head)//hoe gaan we dit de tweede keer oproepen;


//// Tester
// 		2d array printer:
	// y = 0;
	// while(array[y])
	// {
	// 	printf("dubbel array[%s]\n", array[y]);
	// 	y++;
	// }
//Linked list 2d array printer
	t_command		*list;
	int n;
	
	n = 0;
	list = command;
	printf("EIND RESULTAAT TRANSFORM:\n");
	printf("node-builtin = [%d]\n", list->builtin);
	while (list->array[n])
	{
		printf("node-str[%d] = [%s]\n", n, list->array[n]);
		n++;
	}
//// Einde Tester
}