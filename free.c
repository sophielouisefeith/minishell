/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:25 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/12 16:36:23 by SophieLouis   ########   odam.nl         */
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
        head_input = head_input->next;
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
        head_output = head_output->next;
        free(next_output);
    }
    next_output = NULL; 
}

// static void	remove_command(t_command *head, void (*del)(void *))
// {
// 	if (!head)
// 		return ;
// 	del(head->next);
// 	free(head);
// 	head = NULL;
// }


// void        free_list_command(t_command **command)
// {
//   	char					**array;
// 	t_output			    *output;    
// 	t_input			        *input;     
// 	t_command 	            *next;
//     t_command               *new;
//     t_command               *tmp;
//    // t_command               command;
//     t_command               *head;
//     t_command	            *list;
//     // if(!head)
//     //  return ;
    

//     head = *command;
//     while(head != NULL)
//     {
//         tmp = head->next;
//         if(head->array)
//             free(head->array);
//         if(head->builtin)
//             free(head->builtin);
//         if(head->pipe_after)
//             free(head->pipe_after);
//         if(head->sem)
//             free(head->sem);
//         free(head);
//         head = tmp;
//     }

// }
    // head = *command;
    // while(head != NULL)
    // {
    //     tmp = head->next;
    //    if(head->list)
    //         free(head->list);
    //     free(head);
    //     head = tmp;
    // }
//     *command = NULL;
    // extra bescherming of hij ook echt leeg is. 
    // if(array)
    //     free_array(array);
    // if(output)
    //     free_list_output(output);
    // if(input)   
    //     free_list_input(input);
    // free(*command);
//}


// void    free_envlist(t_env **head_origin)
// {
//     t_env *head;
//     t_env *tmp;
//     head = *head_origin;
//     while (head != NULL)
//     {
//         tmp = head->next;
//         if (head->data)
//             free(head->data);
//         free(head);
//         head = tmp;
//     }
//     *head_origin = NULL;
// }

// static void	remove_list(t_lexer *sort)
// {
// 	if (!sort)
// 		return ;
// 	sort = (*sort)->next;
// 	free(sort);
// 	sort = NULL;
// }


// void        free_list_lexer(t_lexer **sort)
// {
//     t_lexer     *tmp;
//     t_lexer     *head;
//     t_lexer     *next;
//     t_lexer		*new;
//     t_lexer 	*list;
//     printf("kom je hier in free list lexor\n");
//     head = *sort;
//     while(head != NULL)
//     {
//         next = head->next;
//         if(new->str)
//             free(new->str);
//         if(new->token)
//             free(new->token);
//         free(head);
//         head = next;
//         //*sort = (*sort)->next;
//         //remove_list(*sort); // dit kan uiteindelijk wel samengengevoegd worden maar nu voor het overzicht 
//     }
//     *sort = NULL;
   // free(lexer); moet dit dan ook nog 
    //vraag nu is heel de struct geleegd of allen head(sort)


      // head = *command;
    // while(head != NULL)
    // {
    //     tmp = head->next;
    //    if(head->list)
    //         free(head->list);
    //     free(head);
    //     head = tmp;
    // }
}

// void            free_complete(int mistake)
// {
//     //printf("kom je nu hier\n");
//     t_lexer     *lexer;
//     t_command   *command;
//     t_lexer     *sort;
//     // t_command   *head;
//     // char        *str;
//     // void        *del;
//     printf("kom je hier in free\n");
//     if(lexer) //of if(lexer)
//         free_list_lexer(&sort);
//    // if(command) // if(head) ik denk head want er dan pas wat gemalloced 
//        // free_list_command(&command);   
// }


// int         free_array(char **array)
// {
//     char **arrayfree;
//     int     i;
    
//     arrayfree = array;
//     i = 0;
//     if(arrayfree[i]!= NULL)
//     {
//         while(arrayfree[i])
//         {
//             free(arrayfree[i]);
//             array[i] = NULL;
//             i++;
//         }
//         free(arrayfree);
//     }
//     return(i);
//}

// void       free_str(char *str)
// {
   
//     if(str != '\0')
//     {
//         // if (/* condition */)
//         // {
//         //     /* code */
//         // }
//         // (str)
//         // {
//         //     free(str);
//         //     str= NULL;
//         //     i++;
//         // }
//         free(str);  // dit is niet nodig 
//     }
//     //return(i);
// }


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