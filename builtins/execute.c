/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/27 13:01:30 by maran         #+#    #+#                 */
/*   Updated: 2020/07/30 16:03:17 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


 //PSEUDOCODE
// void            execute_pipe()
// {
//     int fd[2];
//     int id;

//     if (pipe(fd) == -1)
//     {
//         printf("ERROR in opening the pipe\n");
//         return (1);
//     }
//     id = fork();
//     if (id == -1)
//         printf("ERROR with fork\n");
//     if (id == 0)                        //child
//     {
//         close (fd[0]);
//         builtin(NULL, fd[1]);                 //laat builtins output schrijven naar fd[1]
//         close(fd[1]);
//     }
//     command_head = command_head->next;
//     close (fd[1]);
//     builtin(fd[0], NULL);                      //execute next command met fd[0] input
    
// }

int             execute()
// void            builtin(int fd_0, int fd_1) 
{
    int builtin;
    t_env *env;                         //kopie head

    env = save_env();

    // printf("env = [%p]\n", env);
    // printf("--------ENV BEFORE---------\n");
    // execute_env(env);
    builtin = builtin_exit;
    // if (builtin == builtin_echo)
    //     execute_echo();
    if (builtin == builtin_cd)
        execute_cd();
    if (builtin == builtin_pwd)
        execute_pwd();
    if (builtin == builtin_env)
        execute_env(env);
    if (builtin == builtin_export)
        execute_export(&env);
    if (builtin == builtin_unset)
        execute_unset(&env);
    if (builtin == builtin_exit)
        execute_exit();
    // printf("--------ENV AFTER---------\n");
    // execute_env(env);

    return (0);
}



/*
** Tel aantal nodes. Aantal nodes is aantal processen
** ; --> dan moeten alle processen los van elkaar worden uitgevoerd van links --> rechts
** | tussen processen dan moet proces 1 writen naar fd[1] en proces 2 readen van fd[0]
** > 
**
** TO DO:
** Opnieuw uitzoeken waarom ** ipv * (zucht)
*/

// int             execute()
// {
//     if (command_head->pipe_after)
//         execute_pipe()
//     return (0);
// }
