/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_export.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/28 14:20:02 by maran         #+#    #+#                 */
/*   Updated: 2020/07/28 15:18:27 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


// export command is used to export a variable or function to the environment of all the child processes running in the current shell.
#include "../minishell.h"

/*
** 1. Check of voldoet aan formar name=value
** 2. Check of al in env zit
**   zo ja -->verander value
**   zo nee --> maak nieuw aan
*/


void            execute_export(t_env **env)
{
    char str[] = "USER";


    while(*env)
    {
        if (ft_strcmp(str, (*env)->name));
            *env = (*env)->next;
        else
        {
        //  change value van  
        }
        
              
    }

    
}