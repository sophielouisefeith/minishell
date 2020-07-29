/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:01:30 by maran         #+#    #+#                 */
/*   Updated: 2020/07/28 18:41:25 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Tel aantal nodes. Aantal nodes is aantal processen
** ; --> dan moeten alle processen los van elkaar worden uitgevoerd van links --> rechts
** | tussen processen dan moet proces 1 writen naar fd[1] en proces 2 readen van fd[0]
** > 
**
** TO DO:
** Opnieuw uitzoeken waarom ** ipv * (zucht)
*/

int             execute(void)
{
    int builtin;
    t_env *env;                         //kopie head

    env = save_env();
    
    builtin = builtin_export;
    if (builtin == builtin_cd)
        execute_cd();
    if (builtin == builtin_pwd)
        execute_pwd();
    if (builtin == builtin_env)
        execute_env(&env);
    if (builtin == builtin_export)
    {
        execute_export(&env);
        // execute_env(&env);           //tester
    }
    return (0);
}
