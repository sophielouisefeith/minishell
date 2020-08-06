/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:25 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/06 16:42:36 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


static void         free_list_input(t_list *input)
{
    t_input 	  *list_input;

    while(input != NULL)
    {
        list_input = input;
        list_input = list_input->next_input;
        free(list_input);
    }
    list_input = NULL;
}

static void         free_list_output(t_list *output)
{
    t_output	  *list_output;

    while(output != NULL)
    {
        list_output = *output;
        list_output = list_output->next_output;
        free(list_output);
    }
    list_output = NULL;
}


static void        free_command(t_command *command)
{
  	char					**array;
	int						builtin;
	
	struct s_list			output;    
	struct s_list			input;     
	struct		s_command 	*next;
    
        if(array)
            free_array(array);
        free_list_output(&output);
        free_list_input(&input);
       
}


static void        free_list_lexer(t_lexer *lexer)
{
    //vraag free je hier ook al mee de nodes 
    t_lexer     next;

    while(head != NULL)
    {
        next = head;
        head = head->next;
        free(next);
    }
    next = NULL;
}

static void        free_lexer(t_lexer *lexer)
{
    char        *str;
    int         *token;
    t_lexer     *new;
    t_lexer     *next;
    
        if(str)
            free(str);
        if(token)
            free(token);
        if(next)
            free_list_lexer(lexer); //even uitzoeken moeten we nou heel zo'n struct freen 
        // if(new)
        //     free_struct(new); // dit is met alle nodes er in hoe free je een link list dit gebeurd dan al in next
}


void            free_complete(int mistake)
{
    t_lexer     *lexer;
    t_command   *command;
    
    
    if(mistake)// dit betekend dat er een error is geweest en daarom moet freen
        if(lexer)
            free_lexer(lexer);
        if(command)
            free_command(command);
        //if(env)
           // free(env);

    printf("free because of error\n");     
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

