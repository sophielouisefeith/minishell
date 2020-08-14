/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 16:34:52 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/14 14:23:21 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void         free_input(t_input *input)
{
    t_input       *head_input;
    t_input 	  *next_input;

   
    head_input = input;
    while(head_input != NULL)
    {
        next_input = head_input->next_input;
        // if(head_input->str_input)
        //     free(head_input->str_input);
        free(head_input);
        head_input = next_input; 
    }
    input = NULL;
}

static void         free_output(t_output *output)
{
    t_output	   *tmp;

    while (output != NULL)
    {
        tmp = (output)->next_output;
        // if ((*output)->str_output)
        //     free((*output)->str_output);
        free(output);
        output = tmp; 
    }
    output = NULL; 
}

void        free_array(char **array)
{
    int     y;
    
    y = 0;
    while (array[y])
    {
        // printf("free array: array[y] = %s\n", array[y]);     //WE MALLOCEN DEZE NIET MIJN GOTTIE
        // free(array[y]);
        array[y] = NULL;
        y++;
    }
    free(array);
}  

void        free_list_parser(t_command **command)
{
    t_command   *tmp;

    tmp = NULL;
    while (*command != NULL)
    {
        tmp = (*command)->next_command;
        if ((*command)->array)
            free_array((*command)->array);
        if ((*command)->output)
            free_output((*command)->output);
        if ((*command)->input)
            free_input((*command)->input);
        free(*command);
            *command = tmp;
    } 
    *command = NULL;
}

void        free_list_lexer(t_lexer **sort)
{
    t_lexer     *head_lexer;
    t_lexer     *next_sort;
    
    head_lexer = *sort;
    while(head_lexer != NULL)
    {
        next_sort = head_lexer->next_sort;
        if(head_lexer->str)
            free(head_lexer->str);
        if(head_lexer->token)
            free(head_lexer->token);
        free(head_lexer);
        head_lexer = next_sort; 
    }
    *sort = NULL; 
}

// void        free_list(t_lexer **sort, t_command **command)      //M: Misschien overwegen om vanuit deze functie, de 2 free functies aan te roepen. Voor het overzicht.
// {
//     if (sort)
//         free_list_lexer(sort);
//     if (command)
//         free_list_parser(command);
// }