/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:15 by sfeith        #+#    #+#                 */
/*   Updated: 2020/08/25 12:00:30 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void			execute_command(t_command **command, t_env *env)
{
	// char	**env_array;

	if ((*command)->builtin == builtin_echo)
	{
		echo((*command)->array);
		exit(1);
    } 
	// if ((*command)->builtin == builtin_env)
	// {
	// 	env_array  = env_ll_to_array(env);
	// 	if (execve("execute/env", env_array, NULL) == -1)
	// 		perror("Execve failed!\n");
	// 	save_env(command, env_array);
	// 	printf("Je komt nooit hier terug, tenzij execve faalt\n");
	// 	exit(1);
	// }
}


void			execute_builtin(t_command **command, t_env *env)
{
	

    if ((*command)->builtin == builtin_cd)
        execute_cd(*command, env);
    if ((*command)->builtin == builtin_pwd)
        execute_pwd(*command, env);

    // if ((*command)->builtin == builtin_export)
    //     execute_export(&env);
    // if ((*command)->builtin == builtin_unset)
    //     execute_unset(&env);
    // if ((*command)->builtin == builtin_exit)
    //     execute_exit();
}