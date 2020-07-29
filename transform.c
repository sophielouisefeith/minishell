/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/23 12:07:41 by sfeith        #+#    #+#                 */
/*   Updated: 2020/07/29 15:14:19 by maran         ########   odam.nl         */
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

static int	redirection(t_lexer *head, t_command *command)
{
	int						redirection_greater;
	int						redirection_lesser;
	int						redirection_dgreater;
	
	if((head && head->token[7]))
	{
		//redirection_greater = 1;
		return(redirection_greater = 1);
	}
	if(head && head->token[8])
	{
		//redirection_lesser = 1;
		return(redirection_lesser = 1);
	}
	if(head && head->token[9])
	{
		//redirection_dgreater = 1;
		return(redirection_dgreater = 1);
	}
	return(0);
	printf("ik ben een redirection\n");
	// hier moeten we nog meer meer bepalen wat de input en output is
	
}
static void		out_in_put(t_lexer *head, int i)
{
	t_command		command;
	t_list 			*output; //head
	t_list 			*input;  //head
	t_list 			*output_modus;//head
	t_input			*tmp;
	char			**array_input; // deze moet dus nog gemalloced worden maar even kijken hoe we weten met hoeveel
	int				y;
	int 			pipe_after;
	int				pipe_before;
	int				redirection_greater;
	int				redirection_lesser;
	int				redirection_dgreater;
	int				sem_after;

	output = NULL;
	input = NULL;
	// printf("pipeafter out_int [%d]\n", pipe_after);
	// printf ("int i = [%d]\n", i);

	// if(pipe_after)
	// {
	// 	printf("array[%s]\n", *command.array); // dit doet het dus wel 
	// 	array_input[y] = *command.array;
	// 	// y++;
	// }
	if(redirection_dgreater || pipe_after || redirection_greater||sem_after)
	{
		while(*command.array)
		{
			printf("array[%s]\n", *command.array); // dit doet het dus wel 
			array_input[y] = *command.array;
			*command.array = *command.array++;
		}
	}
	else
		//array_input[y] = input;
		y++;
		input = input->next;
	if(pipe_before)
	{
		printf("array[%s]\n", *command.array); // dit doet het dus wel 
			array_input[y] = *command.array;
			*command.array = *command.array++;
	}
	
	// if(i == sem_after)
	// 	printf("sem");
	// if(i == redirection_greater)
	// if(i == redirection_lesser)
	// if(i == redirection_dgreater)

// nu willen we het gewoon in de volgende node stoppen 
	// tmp = ll_new_node_command(array_input, i);
	// ll_lstadd_back_command(&command, tmp);	
	
}

static int		fill_operator(t_lexer *head)
{
	t_command command;
	int pipe_after;
	int sem_after;
	
	if(head && head->token[token_pipe])
		return(pipe_after = 1);
		printf("pipeafter[%d]\n", pipe_after);
		// misschien zouden we hier al wel input en output kunnen doen // hier zouden we gelijk naar input_output functie kunnen gaan
	if(head && head->token[token_semicolon])
		return(sem_after = 1);
	if((head && head->token[7])||(head && head->token[8])\
	|| (head && head->token[9]))
		return(redirection(head, &command));
	return(0);
}

static int			command_next(t_command *command, t_lexer *head)
{
 
	int		pipe_after;
	int		pipe_before;
	int		sem_after;
	int		sem_before;
	int		redirection_greater;
	int		redirection_lesser;
	int		redirection_dgreater;
	
	//  eerst even gaan kijken met de redirections want dan word het dus input of output
	// dan gaan we in de volgende daar gebeurt eigenlijk precies hetzelfde maar dan moeten we wel even 
	// de pipe en semicolum op after zetten 
	if(pipe_after == 1 && command)
	{
		pipe_after = 0; // denk misschien niet nodig omdat we  niet ++ maar in de after operator er een 1 aan geven.
		command = command->next;
		return(pipe_before = 1);
	}
	if(sem_after == 1 && command)
	{
		printf("er is een semicolum");
		command = command->next;
		return(sem_before = 1);
	}
	if((redirection_greater || redirection_dgreater || redirection_lesser) && command)
	{
		command = command->next;
		return(redirection(head, command));
	}
		
	// nu hebben we de input en output ook gevuld van de eerste node van de command struct nu gaa we naar de tweede node en doen 
	//hetzelfde riedeltje opnieuw
	command = command->next; // hier gaan we naar de volgende node in de commanstruct
	//en nu gaan we er dan nog een keer in
	//transform(head);
	return(0);
}

void				transform(t_lexer *head)
{
	char 		**array;
	char 		*newstr;
	int 		type_built;
	int 		num_nodes;
	int 		y;
	int			operator;
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
	//printf("head->str = [%s]\n", head->str);
	tmp = ll_new_node_command(array, type_built);
	ll_lstadd_back_command(&command, tmp);
	operator = fill_operator(head);
	printf("operator[%d]\n", operator);
	//we weten nu wat alle dingen zijn nu moeten we bepalen of het input of output is
	out_in_put(head, operator);
	operator = command_next(command, head);
	transform(head);
	//out_in_put(&command, operator);
	
	

	

	

	
		

//// Tester
// 		2d array printer:
// 	y = 0;
// 	while(array[y])
// 	{
// 		printf("dubbel array[%s]\n", array[y]);
// 		y++;
// 	}
// //Linked list 2d array printer
// 	t_command		*list;
// 	int n;
	
// 	n = 0;
// 	list = command;
// 	printf("EIND RESULTAAT TRANSFORM:\n");
// 	printf("node-builtin = [%d]\n", list->builtin);
// 	while (list->array[n])
// 	{
// 		printf("node-str[%d] = [%s]\n", n, list->array[n]);
// 		n++;
// 	}
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
		

