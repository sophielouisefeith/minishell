/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:25 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/11 08:09:26 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void         free_list_input(t_input *input)
{
    t_input       *head_input;
    t_input 	  *next_input;

    while(head_input != NULL)
    {
        next_input = head_input;
        head_input = head_input->next_input;
        free(next_input);
    }
    next_input = NULL; 
}

static void         free_list_output(t_output *output)
{
    t_output       *head_output;
    t_output	   *next_output;

    while(head_output != NULL)
    {
        next_output = head_output;
        head_output = head_output->next_output;
        free(next_output);
    }
    next_output = NULL; 
}


static void        free_command(t_command *command)
{
  	char					**array;
	t_output			    *output;    
	t_input			        *input;     
	t_command 	            *next;
    t_command               *new;
    t_command               *head;
    
    if(array)
        free_array(array);
    free_list_output(output);
    free_list_input(input);
    while(head != NULL)
    {
        next = head;
        head = head->next;
        free(next);
    }
    next = NULL;
    
       
}


static void        free_list_lexer(t_lexer *lexer)
{
    //vraag free je hier ook al mee de nodes 
    t_lexer     *next;
    t_lexer     *sort;

    while(sort != NULL)
    {
        next = sort;
        sort = sort->next;
        free(next);
    }
    next = NULL;
}

// static void        free_lexer(t_lexer **lexer)
// {
//     // printf("inlexerfree\n");
//     // char        *str;
//     // int         *token;
//     // t_lexer     *new;
//     // t_lexer     *next;
    
//         // if(lexer->str)
//         //     free(str);
//         // if(next)
//         //     free_list_lexer(lexer); //even uitzoeken moeten we nou heel zo'n struct freen 
//         // if(new)
//         //     free_struct(new); // dit is met alle nodes er in hoe free je een link list dit gebeurd dan al in next
// }


void            free_complete(int mistake)
{
     printf("kom je nu hier\n");
    t_lexer     *lexer;
    t_command   *command;
    char        *str;
    
    // if(mistake) == 2) // No such file or directory dan zijn er nog geen structs aangemaakt
        
    //     return(0);
    //     break ;
        
    // if(!mistake)
    //     free_error(errno); dubbel op protection 
   // printf("str[%s]\n", lexer->str);
   // if(mistake)// dit betekend dat er een error is geweest en daarom moet free
        if(lexer)
        {
            printf("fout in lexer\n");
            free_list_lexer(lexer);
        }
        if(command)
            free_command(command);
        // if(env)
        //    free(env);

    //printf("free because of error\n");     
}


int         free_array(char **array)
{
    char **arrayfree;
    int     i;
    
    arrayfree = array;
    i = 0;
    if(arrayfree[i]!= NULL)
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

void       free_str(char *str)
{
   
    if(str != '\0')
    {
        // if (/* condition */)
        // {
        //     /* code */
        // }
        // (str)
        // {
        //     free(str);
        //     str= NULL;
        //     i++;
        // }
        free(str);  // dit is niet nodig 
    }
    //return(i);
}

