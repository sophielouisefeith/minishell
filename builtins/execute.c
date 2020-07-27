/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:01:30 by maran         #+#    #+#                 */
/*   Updated: 2020/07/27 17:19:04 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int             execute(void)
{
    int builtin;
    int builtin2;
    // Tel aantal nodes. Aantal nodes is aantal processen
    int num_nodes = 3;

    // ; --> dan moeten alle processen los van elkaar worden uitgevoerd van links --> rechts
    // | tussen processen dan moet proces 1 writen naar fd[1] en proces 2 readen van fd[0]
    // >

    builtin = builtin_cd;
    builtin2 = builtin_pwd;
    if (builtin == builtin_cd)
        execute_cd();
    if (builtin2 == builtin_pwd)
        execute_pwd();

    return (0);
}