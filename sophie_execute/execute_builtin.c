/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:15 by sfeith        #+#    #+#                 */
/*   Updated: 2020/08/24 15:36:52 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void             execute_command(t_command **command)  
{
	if ((*command)->builtin == builtin_echo)
    {
    	if (execve("sophie_execute/echo", (*command)->array, NULL) == -1)
    		perror("Execve failed!\n");
        printf("Je komt nooit hier terug, tenzij execve faalt\n");
        exit(1);
    } 
}

void             execute_builtin(t_command **command)
{

	// char *buf;
    // t_env *env;
    // env = save_env();

    // printf("env = [%p]\n", env);
    // printf("--------ENV BEFORE---------\n");
    // execute_env(env);
    // printf("IN EXECUTE_BUILTIN\n");
    // if ((*command)->builtin == builtin_echo)
    // {
    //      if (execve("sophie_execute/echo", (*command)->array, NULL) == -1)
    //         perror("Execve failed!\n");
    //     printf("Je komt nooit hier terug, tenzij execve faalt\n");
    //     exit(1);
    // } 
    if ((*command)->builtin == builtin_cd)
        execute_cd(*command);
    if ((*command)->builtin == builtin_pwd)
        execute_pwd(*command);
    // if ((*command)->builtin == builtin_env)
    //     execute_env(env); //buf.
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