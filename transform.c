/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 12:07:41 by sfeith        #+#    #+#                 */
/*   Updated: 2020/07/23 16:35:34 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** >>>>>>> TO DO <<<<<<<<<<<<<< 
** 1. use the link list from the lexer go trough every node to check on ' "" | ;
** 2. save if ; | before after. remove '  ""
** 3. place the nodes in a new struct the command struct 
** 4. you can make use of the execve function  int
     execve(const char *path, char *const argv[], char *const envp[]);
*/

/* notes regarding this function for maran and sophie  */
void				transform(t_lexer *list)
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
	int n;
	int i;
	int len;
	char *newstr;

	len = ft_strlen(list->str);
	n = 0;
	printf("node-str = [%s]\n", list->str);
	if(list->token[3]  || list->token[4])
	{
		printf("he je bent een quote\n");
		len = len - 2;
		newstr= ft_substr(list->str, 1, len);
		printf("parser-str[%s]\n", newstr );
	}
	// if(list->token[5])
	// {
	// 	printf("je bent een pipeline\n");
	// 	if(list->next == )
	// 	command->pipe_before = 
	// 	command->pipe_after =
	// }
	// if(list->token[6])
	// {
	// 	printf("je bent een semicoln\n");
	// 	if(list->next == )
	// 	command->pipe_before = 
	// 	command->pipe_after =
	// }
	















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
		

}