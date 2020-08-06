/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:25 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/06 11:53:40 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


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