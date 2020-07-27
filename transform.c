/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 12:07:41 by sfeith        #+#    #+#                 */
/*   Updated: 2020/07/27 14:04:18 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** >>>>>>> TO DO <<<<<<<<<<<<<< 
** 1. use the link list from the lexer go trough every node to check on ' "" | ;
** 2. save if ; | before after. remove '  ""
** 3. place the nodes in a new struct the command struct 
** 
*/

static int				count_node(t_lexer *head)
{
	t_lexer   *count_node;
	int 				i;

	i = 0;
	count_node = head;
	while(count_node && count_node->token[token_general])
	{
		i++;
		count_node = count_node->next;
	}
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

	while (head && head->token[token_general])
	{
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
	
	printf("head->str = [%s]\n", head->str);

	if(head && head->token[token_pipe])
	{
		printf("kom er maar in\n");
		
		// if(head->token[token_pipe])
		// // pipe()
		// 	printf("je bent een pipeline\n");
		// if(head->token[token_semicolon])
		// 	printf("je bent een semicoln\n");
	}
	
	// tmp = ll_new_node_command(array, type_built);
	// ll_lstadd_back_command(&command, tmp);
	
	// command = command->next;
	
		

//// Tester
// 		2d array printer:
	// y = 0;
	// while(array[y])
	// {
	// 	printf("dubbel array[%s]\n", array[y]);
	// 	y++;
	// }
//		Linked list 2d array printer
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


	// if(head->token[token_pipe])
	// 	printf("je bent een pipeline\n");
	// if(head->token[token_semicolon])
	// 	printf("je bent een semicoln\n");

	/* hier komt 1 node per keer binnen want deze functie word aangeroepen in de lexer vanuit een while loop  
	dus nu hebben we de eerste node */
	


/*   token string dan stoppen we hem in transform en dan geven we hem terug als een string dit is het enige wat er gaat gebeuren in transform
maar je moet wel kijken wat er relevant is om in te stoppen en of het input of output gaat zijn*/


	/*nu wil ik dus per node gaan kijken en gaan transformen hiervoor gebruik ik execve dit 
	gebruik ik pas als ik de tekenstjes heb opgeslagen*/

	/*eerst heb ik dus oude en de nieuwe node nodig om elkaar te kunne overschrijven  */

	// if((pid = fork ()) == -1)
	// 	printf("here comes an error execve was not succesfull");
	// else if (pid == 0)
	// {
		
	// }
		

