/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/20 11:57:16 by maran         #+#    #+#                 */
/*   Updated: 2020/08/24 16:19:37 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			execute_builtin(t_command **command, t_env *env)
{
	char	**env_array;
		
	if ((*command)->builtin == builtin_echo)
	{
		if (execve("maran_execute/echo", (*command)->array, NULL) == -1)
			perror("Execve failed!\n");
		printf("Je komt nooit hier terug, tenzij execve faalt\n");
		exit(1);
    } 
    // if ((*command)->builtin == builtin_cd)
    //     execute_cd(*command);
    // if ((*command)->builtin == builtin_pwd)
    //     execute_pwd();
	if ((*command)->builtin == builtin_env)
	{
		env_array  = env_ll_to_array(env);
		if (execve("maran_execute/env", env_array, NULL) == -1)
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
}