/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   free.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:25 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/08/06 11:23:49 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int         free_array(char **array)
{
    
    int     i;

    i = 0;
    if(array[i]!= NULL)
    {
        while(array[i])
        {
            free(array[i]);
            array[i] = NULL;
            i++;
        }
        free(array);
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
        free(str);
    }
    //return(i);
}