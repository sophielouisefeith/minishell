/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   input.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/31 09:38:34 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/07/31 10:32:56 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



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

void            input_fill(t_lexer *head, char **array, int *y)
{

    char					*in;
    char                    *str_input;
    t_input                 *tmp_input;
    t_input                 input;
    t_input                 *input_head; //head
     int                    token_input;

    input_head = NULL;
	in = head->str;

  
    printf("input[%s]\n", in);
    token_input = check_token(in);
    head = head->next;
    str_input = head->str;
    printf("filename input[%s]\n", str_input);
    head = head->next;
    if(get_token_type(head->str, *y) == head->token[token_general])                                         //dat betekend dat er nog iets achter de filename staat
        array[*y] = head->str;
         printf("array[%s]\n", array[*y]);
    // input_head = input_head->next_input;  // nu naar de volgende node 
    tmp_input = ll_new_node_input(str_input, token_input);
	ll_lstadd_back_input(&input_head, tmp_input);
    
}