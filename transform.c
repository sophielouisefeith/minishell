/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/07/31 09:36:07 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				count_node(t_lexer *head)
{
	t_lexer   *count_node;
	int 				i;

	i = 0;
	count_node = head;
	while(count_node && (count_node->token[token_general]||count_node->token[7|8|9]))
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






t_input			*ll_new_node_input(void *content, int token_output)
{
	t_input		*new;

	new = (t_input *)malloc(sizeof(t_input));
	if (!new)
		return (0);
	new->str_input = content;
	new->token_input = token_output;
	new->next_input = NULL;
	return (new);
}


void			ll_lstadd_back_input(t_input **head_input, t_output *new_input)
{
	t_input		*list_input;

	list_input = *head_input;
	if (list_input)
	{
		while (list_input->next_input)
			list_input = list_input->next_input;
		list_input->next_input = new_input;
	}
	else
		*head_input = new_input;
}



static void	redirection(t_lexer *head, char **array, int *y)
{
	int						redirection_greater;
	int						redirection_lesser;
	int						redirection_dgreater;
	char					*out;
    char                    *str_input;
    char                    *str_output;
    t_output                output;
    t_output                *output_head; //head
    t_output                *tmp_output;
    t_input                 *tmp_input;
    t_input                 input;
    t_input                 *input_head; //head
    int                     token_output;
    int                     token_input;
    

    
    // output_head = NULL;
	// out = head->str;
    while((head) && (head->token[7]||(head && head->token[9])))                                        //dit moet dus veranderd naar output_head
    { 
        output_fill(head, array, &y);
        // printf("waar zijn we nu in de node[%s]\n", out);
        // token_output = check_token(out);
        // head = head->next;
        // str_input = head->str;
        // printf("filename[%s]\n", str_input);
        // head = head->next;
        // // if(get_token_type(head->str, *y) == head->token[token_general])                                         //dat betekend dat er nog iets achter de filename staat
        // //     array[*y] = head->str;
        // //     printf("array[%s]\n", array[*y]);
        // //output_head = output_head->next_output;  // nu naar de volgende node 
        // tmp_output = ll_new_node_output(str_input, token_output);
	    // ll_lstadd_back_output(&output_head, tmp_output);
    }
    
    while(head && head->token[8])                                        //dit moet dus veranderd naar output_head
    { 
        printf("input[%s]\n", out);
        token_input = check_token(out);
        head = head->next;
        str_output = head->str;
        printf("filename[%s]\n", str_output);
        head = head->next;
        // if(get_token_type(head->str, *y) == head->token[token_general])                                         //dat betekend dat er nog iets achter de filename staat
        //     array[*y] = head->str;
        //     printf("array[%s]\n", array[*y]);
        //output_head = output_head->next_output;  // nu naar de volgende node 
        tmp_input = ll_new_node_output(str_output, token_output);
	    ll_lstadd_back_output(&output_head, tmp_input);
    }
    
	// while((head && (head->token[7]|| head->token[9])))
	// {
	// 	array[*y] = filename;
	// 	printf("array[%s]\n ", array[*y]);
	// 	head = head->next;
	// 	*y++;
	// }
	// head = head->next;
	// //newstr = NULL;
	// newstr = head->str;
	// printf("waar zijn we nu in de node[%s]\n", head->str);
	// while(head && (head->token[token_general]))
	// {
	// 	array[*y] = newstr;
	// 	head = head->next;
	// 	printf("array[%s]\n ", array[*y]);
	//  	*y++;
	// }
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
			array_input[y] = *command.array; // dit moet output zin 
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
	// if((head && head->token[7])||(head && head->token[8])\
	// || (head && head->token[9]))
	// 	return(redirection(head, &command));
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

	printf("kom je in transform\n");
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
	printf("waar zijn we nu in de node[%s]\n", head->str);
	if((head && head->token[7])||(head && head->token[8])\
	|| (head && head->token[9]))
		redirection(head, array, &y);
	
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
}