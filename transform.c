/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   transform.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 08:13:15 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/07/31 11:59:30 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int				count_node(t_lexer *head)
{
    // meer ruimte doortellen tot een redirector, overslaan en dan nog een keer kijken voor general
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





static void	redirection(t_lexer *head)
{
	// int						redirection_greater;
	// int						redirection_lesser;
	// int						redirection_dgreater;
	// char					*out;
    // char                    *str_input;
    // char                    *str_output;
    // t_output                output;
   // t_output                *output_head; //head
    // t_output                *tmp_output;
    // t_input                 *tmp_input;
    // t_input                 input;
    // t_input                 *input_head; //head
    // int                     token_output;
    // int                     token_input;
    

    
    // output_head = NULL;
	// out = head->str;
    // output_head = head;
    while(head)                                         //dit moet dus veranderd naar output_head
    { 
        if(head->token[7]|| head->token[9])
            output_fill(head);
        head = head->next;
        //hier checkken of er nog iets achter de redirection staat 
        if(head->token[8])
            input_fill(head);
        head = head->next;
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
    // while(head && head->token[8])                                        //dit moet dus veranderd naar output_head
    // { 
    //     input_fill(head, array, &y);
    //     head = head->next;
        // printf("input[%s]\n", out);
        // token_input = check_token(out);
        // head = head->next;
        // str_output = head->str;
        // printf("filename[%s]\n", str_output);
        // head = head->next;
        // // if(get_token_type(head->str, *y) == head->token[token_general])                                         //dat betekend dat er nog iets achter de filename staat
        // //     array[*y] = head->str;
        // //     printf("array[%s]\n", array[*y]);
        // //output_head = output_head->next_output;  // nu naar de volgende node 
        // tmp_input = ll_new_node_output(str_output, token_output);
	    // ll_lstadd_back_output(&output_head, tmp_input);
 //   }
    
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






// static void		out_in_put(t_lexer *head, int i)
// {
// 	t_command		command;
// 	t_list 			*output; //head
// 	t_list 			*input;  //head
// 	t_list 			*output_modus;//head
// 	t_input			*tmp;
// 	char			**array_input; // deze moet dus nog gemalloced worden maar even kijken hoe we weten met hoeveel
// 	int				y;
// 	int 			pipe_after;
// 	int				pipe_before;
// 	int				redirection_greater;
// 	int				redirection_lesser;
// 	int				redirection_dgreater;
// 	int				sem_after;

// 	output = NULL;
// 	input = NULL;
// 	// printf("pipeafter out_int [%d]\n", pipe_after);
// 	// printf ("int i = [%d]\n", i);

// 	// if(pipe_after)
// 	// {
// 	// 	printf("array[%s]\n", *command.array); // dit doet het dus wel 
// 	// 	array_input[y] = *command.array;
// 	// 	// y++;
// 	// }
// 	if(redirection_dgreater || pipe_after || redirection_greater||sem_after)
// 	{
// 		while(*command.array)
// 		{
// 			printf("array[%s]\n", *command.array); // dit doet het dus wel 
// 			array_input[y] = *command.array;
// 			*command.array = *command.array++;
// 		}
// 	}
// 	else
// 		//array_input[y] = input;
// 		y++;
// 		input = input->next;
// 	if(pipe_before)
// 	{
// 		printf("array[%s]\n", *command.array); // dit doet het dus wel 
// 			array_input[y] = *command.array; // dit moet output zin 
// 			*command.array = *command.array++;
// 	}
	
// 	// if(i == sem_after)
// 	// 	printf("sem");
// 	// if(i == redirection_greater)
// 	// if(i == redirection_lesser)
// 	// if(i == redirection_dgreater)

// // nu willen we het gewoon in de volgende node stoppen 
// 	// tmp = ll_new_node_command(array_input, i);
// 	// ll_lstadd_back_command(&command, tmp);	
	
// }

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
    //maakt nog geen nieuwe node aan. 
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

	while((head) && (head->token[token_general]||head->token[7] ||head->token[8]|| head->token[9]))
	{
        while(head->token[7] ||head->token[8]|| head->token[9])
            head = head->next->next;
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
	if((head && head->token[7])||(head && head->token[8])\
	|| (head && head->token[9]))
		redirection(head);
	tmp = ll_new_node_command(array, type_built);
	ll_lstadd_back_command(&command, tmp);
	fill_operator(head);
	command_next(command, head);
	//transform(head)//hoe gaan we dit de tweede keer oproepen;


//// Tester
// 		2d array printer:
	y = 0;
	while(array[y])
	{
		printf("dubbel array[%s]\n", array[y]);
		y++;
	}
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