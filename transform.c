/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 12:07:41 by sfeith        #+#    #+#                 */
/*   Updated: 2020/07/24 16:28:23 by SophieLouis   ########   odam.nl         */
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
	while(count_node && count_node->token[token_general])
	{
		i++;
		count_node = count_node->next;
	}
	array = (char **)malloc((i + 1) * sizeof(char *));

		
		// m = 0;
		// while (m < 11)
		// {
		// 	printf("%d=[%d]  ", m, head->token[m]);
		// 	m++;
		// }
		// printf("\n");
	// if(head->token[token_general])
	// 	printf("TRUE\n");

	// if(head->token[token_general])
	// {
	// 	//printf("halo\n");
	// 	if(head->token[token_quote]  || head->token[token_dquote])
	// 		newstr = trunc_quotes(head, head->str);
	// 	//printf("newstr= [%s]\n", newstr);
	// 	array[y] = newstr;
	// 	y++;
	// 	//printf("array =  [%s]\n", array[0]);
	// 	type_built = get_builtin_type(head->str);
	// 	//tmp = ll_new_node_command(newstr, type_built);
	// 	head = head->next;
	// }
	while(head && head->token[token_general])
	{
		if(y == 0 )
		{
			//printf("halo\n");
			if(head->token[token_quote]  || head->token[token_dquote])
				newstr = trunc_quotes(head, head->str);
		printf("newstr= [%s]\n", newstr);
			array[y] = newstr;
			y++;
		//printf("array =  [%s]\n", array[0]);
			type_built = get_builtin_type(head->str);
		//tmp = ll_new_node_command(newstr, type_built);
			head = head->next;
			
		}
		if(head->token[token_quote] || head->token[token_dquote])
		{
			newstr = trunc_quotes(head, head->str);
			printf("newstr= [%s]\n", newstr);
			array[y] = newstr;
			//printf("array2 =  [%s]\n", array[1]);
		}
		else
			array[y] = head->str;
		// printf("array2 =  [%s]\n", array[y]);
		y++;
		head = head->next;
		
	}

	//printf("newstr= [%s]\n", newstr);
	// if(array)
	// array[y]= 0;
	// printf("dubbel array 1[%s]\n", array[0]);
	// printf("dubbel array 1[%s]\n", array[1]);
	// printf("dubbel array 1[%s]\n", array[2]);
	
	// y = 0;
	// while(array[y])
	// {
	// 	printf("dubbel array[%s]\n", array[y]);
	// 	y++;
	// }
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
		

