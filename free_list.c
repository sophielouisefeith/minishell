/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free_list.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/12 16:34:52 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/12 17:04:51 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void        free_list(t_lexer **sort, t_command *command)
{
    t_lexer     *head;
    t_lexer     *next;
    t_lexer     *new;
 
    head = *sort;
    while(head != NULL)
    {
        next = head->next;
        if(new->str)
            free(new->str);
        if(new->token)
            free(new->token);
        free(head);
        head = next;
        //*sort = (*sort)->next;
        //remove_list(*sort); // dit kan uiteindelijk wel samengengevoegd worden maar nu voor het overzicht 
    }
    *sort = NULL;
}