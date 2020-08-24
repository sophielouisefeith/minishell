/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 11:57:16 by maran         #+#    #+#                 */
/*   Updated: 2020/08/24 14:20:34 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void             execute_builtin(t_command **command)
{

    // char *buf;
    // t_env *env;
    // env = save_env();

    // printf("env = [%p]\n", env);
    // printf("--------ENV BEFORE---------\n");
    // execute_env(env);
    // printf("IN EXECUTE_BUILTIN\n");
    if ((*command)->builtin == builtin_echo)
    {
         if (execve("maran_execute/echo", (*command)->array, NULL) == -1)
            perror("Execve failed!\n");
        printf("Je komt nooit hier terug, tenzij execve faalt\n");
        exit(1);
    } 
    // if ((*command)->builtin == builtin_cd)
    //     execute_cd();
    // if ((*command)->builtin == builtin_pwd)
    //     execute_pwd();
    if ((*command)->builtin == builtin_env)
    {
		// make 2d arryay
		array  = llto2d(env)
		
         if (execve("maran_execute/env", (*command)->array, NULL) == -1)
            perror("Execve failed!\n");
        printf("Je komt nooit hier terug, tenzij execve faalt\n");
        exit(1);
    }
    // if ((*command)->builtin == builtin_export)
    //     execute_export(&env);
    // if ((*command)->builtin == builtin_unset)
    //     execute_unset(&env);
    // if ((*command)->builtin == builtin_exit)
    //     execute_exit();
    // printf("--------ENV AFTER---------\n");
    // execute_env(env);
    // return (buf);
}