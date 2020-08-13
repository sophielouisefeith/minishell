/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 16:34:52 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/13 19:42:56 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void         free_input(t_input *input)              //M: Zelfde schrijfstijl aanhouden als bij de andere free
{
    t_input       *head_input;
    t_input 	  *next_input;

    
    head_input = input;
    while(head_input != NULL)
    {
        next_input = next_input->next_input;
        if(head_input->str_input)
            free(head_input->str_input);
        free(head_input);
        head_input = next_input; 
    }
    input = NULL; 
     printf("---------input is free\n");
}

static void         free_output(t_output *output)           //M: Zelfde schrijfstijl aanhouden als bij de andere free
{
    t_output       *head_output;
    t_output	   *next_output;
    
    printf("---------kom je in output\n");
    head_output = output;
    while(head_output != NULL)
    {
        next_output = next_output->next_output;
        if(head_output->str_output)
            free(head_output->str_output);
        // if(head_output->token)
        //     free(head_output->token);
        free(head_output);
        head_output = next_output; 
    }
    output = NULL; 
    printf("---------output is free\n");
}

void        free_array(char **array)
{
    char **arrayfree;
    int     i;
    
    arrayfree = array;
    i = 0;
    while(arrayfree[i])
    {
        free(arrayfree[i]);
        array[i] = NULL;
        i++;
    }
    free(arrayfree);
    printf("----------array is free\n");
    //return(i);
}

void        free_list_parser(t_command *command)
{
    t_command   *next_command;
    t_command   *head_parser;

    printf("----------command is free\n");
    head_parser = command;
    while(head_parser  != NULL)
    {
        next_command = head_parser->next_command;
        if(head_parser->array)
            free_array(head_parser->array);
        //if(head_parser->builtin)
        //free(head_parser->builtin);
       // head_parser->builtin = NULL;
       printf("---------hier stop je dus\n");
        if(head_parser->output)
        {
            printf("---------wil je hier wel in\n");
            free_output(head_parser->output);
        }
        if(head_parser->input)
            free(head_parser->input);
        // if(head_parser->pipe_after)
        //     free(head_parser->pipe_after);
        // if(head_parser->pipe_before)
        //     free(head_parser->pipe_before);
        // if(head_parser->sem)
        //     free(head_parser->sem);
        free(head_parser);
        head_parser  = next_command;
        command = NULL;
    } 
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
    printf("---------lexer is free\n");
}

void        free_list(t_lexer **sort, t_command *command)      //M: Misschien overwegen om vanuit deze functie, de 2 free functies aan te roepen. Voor het overzicht.
{
    if(sort)
        free_list_lexer(sort);
    if(command)
        free_list_parser(command);
}