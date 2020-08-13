/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 16:34:52 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/13 09:50:58 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void         free_input(t_input *input)              //M: Zelfde schrijfstijl aanhouden als bij de andere free
{
    t_input       *head_input;
    t_input 	  *next_input;

    while(head_input != NULL)
    {
        next_input = head_input;
        head_input = head_input->next;
        free(next_input);
    }
    next_input = NULL; 
}

static void         free_output(t_output *output)           //M: Zelfde schrijfstijl aanhouden als bij de andere free
{
    t_output       *head_output;
    t_output	   *next_output;
                                                            //M: head_output = *output;
    while(head_output != NULL)
    {
        next_output = head_output;
        head_output = head_output->next;
        free(next_output);
    }
    next_output = NULL; 
}

int         free_array(char **array)
{
    char **arrayfree;
    int     i;
    
    arrayfree = array;
    i = 0;
    if(arrayfree[i]!= NULL)                                     //M: If niet dubbel op met while?
    {
        while(arrayfree[i])
        {
            free(arrayfree[i]);
            array[i] = NULL;
            i++;
        }
        free(arrayfree);
    }
    return(i);
}


void        free_list(t_lexer **sort, t_command *command)      //M: Misschien overwegen om vanuit deze functie, de 2 free functies aan te roepen. Voor het overzicht.
{
    
    t_command   *next_command;
    t_command   *head_parser;
    t_lexer     *head_lexer;
    t_lexer     *next;
    
    if(sort)
    {
        head_lexer = *sort;
        if(!head_lexer)                                          //M: dit is niet nodig denk ik, of wel?
            printf("ben jij de seg\n");
        while(head_lexer != NULL)
        {
            printf("----------head str\n");
            next = head_lexer->next;
        printf("----------head str->next\n");
            if(head_lexer->str)
            {
                printf("----------free str\n");
                free(head_lexer->str);
            }
            if(head_lexer->token)
            {
                printf("----------free token\n");
                free(head_lexer->token);
            }
                printf("---------alles free\n");
            free(head_lexer);
            head_lexer = next;
        }
        *sort = NULL;
    }
    
    if(command)
    {
        head_parser = command;
        if(!head_parser )
            printf("command struct\n");
        while(head_parser  != NULL)
        {
            next_command = head_parser->next_command;
            if(head_parser->array)
            {
                free_array(head_parser->array);
            }
            // if(head_parser->builtin)
            // {
            //     free(head_parser->builtin);
            // }
            if(head_parser->output)
            {
                free_output(head_parser->output);
            }
            if(head_parser->input)
            {
                free(head_parser->input);
            }
            // if(head_parser->pipe_after)
            // {
            //     free(head_parser->pipe_after);
            // }
            // if(head_parser->pipe_before)
            // {
            //     free(head_parser->pipe_before);
            // }
            // if(head_parser->sem)
            // {
            //     free(head_parser->sem);
            // }
            free(head_parser);
            head_parser  = next_command;
        }
        command = NULL;
    }
}