/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:01:30 by maran         #+#    #+#                 */
/*   Updated: 2020/07/28 15:09:22 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
    // Tel aantal nodes. Aantal nodes is aantal processen
    // int num_nodes = 3;

    // ; --> dan moeten alle processen los van elkaar worden uitgevoerd van links --> rechts
    // | tussen processen dan moet proces 1 writen naar fd[1] en proces 2 readen van fd[0]
    // >

int             execute(void)
{
    int builtin;
    t_env **env;

    *env = save_env();
    
    builtin = builtin_env;
    if (builtin == builtin_cd)
        execute_cd();
    if (builtin == builtin_pwd)
        execute_pwd();
    if (builtin == builtin_env)
        execute_env(env);
    if (builtin == builtin_export)
        execute_export(env);

    return (0);
}