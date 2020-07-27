/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 12:07:41 by sfeith        #+#    #+#                 */
/*   Updated: 2020/07/24 16:53:02 by SophieLouis   ########   odam.nl         */
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




// t_command			*ll_new_node_command(void *content, int *token, int len)
// {
// 	t_lexer		*new;

// 	new = (t_lexer *)malloc(sizeof(t_lexer));
// 	if (!new)
// 		return (0);
// 	new->str = content;
// 	new->token = token;
// 	new->next = NULL;
// 	return (new);
// }

/* notes regarding this function for maran and sophie  */




void				transform(t_lexer *head)
{

	//t_lexer *lexer;
	//t_parser    *commandlist;
	//pid_t		pid;
	//t_lexer		token;

	//printf("node-trans = [%s]\n", list->str);
	//printf("token = [%d]\n", list->token[0]);
	//if(&token[1] == 1)
	/* een node komt binnen die moeten we gaan controleren  en weer terug geven als een str*/
	t_command *command;
	t_command *tmp;
	t_lexer   *count_node;
	int n;
	int i;
	//int len;
	char *newstr;
	int	 *builtin;
	int type_built;
	char **array;
	int y;
	int m;

	// len = ft_strlen(head->str);
	n = 0;
	builtin = intspace(8);
	i = 0;
	y = 0;
	count_node = head;
	i = node_count(count_node, i);
	array = (char **)malloc((i + 1) * sizeof(char *));
	if (array == NULL)
		printf("Malloc failed\n");
	if(head->token[token_general])
	{
		if(head->token[token_quote]  || head->token[token_dquote])
		{
			newstr = trunc_quotes(head, head->str);
			array[y] = newstr;
		}
		else
			array[y] = head->str;
		y++;
		// type_built = get_builtin_type(head->str);
		//tmp = ll_new_node_command(newstr, type_built);
		head = head->next;
	}
	while(head && head->token[token_general])
	{
		if(head->token[token_quote] || head->token[token_dquote])
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

	y = 0;
	while(array[y])
	{
		printf("dubbel array[%s]\n", array[y]);
		y++;
	}
	// if(head->token[token_pipe])
	// 	printf("je bent een pipeline\n");
	// if(head->token[token_semicolon])
	// 	printf("je bent een semicoln\n");
	
}














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
		

