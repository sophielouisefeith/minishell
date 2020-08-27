/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:15 by sfeith        #+#    #+#                 */
/*   Updated: 2020/08/27 15:25:05 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** TO DO !:
Each shell command returns an exit code when it terminates, either successfully or unsuccessfully.

----------
echo : The return status is 0 unless a write error occurs
cd: The return status is zero if the directory is successfully changed, non-zero otherwise.
pwd: The return status is zero unless an error is encountered while determining the name of the current directory or an invalid option is supplied.
export: The return status is zero unless an invalid option is supplied or one of the names is not a valid shell variable name
unset: The return status is zero unless a name is readonly.
env: The env utility exits 0 on success, and >0 if an error occurs.  An exit status of 126 indicates that utility was found, but could not be executed.  An exit status of 127 indicates that utility could not be found.
-----------

Simple shell command: echo
*/


void			execute_command(t_command **command, t_env **_env)
{
	char	**env_array;
	int 	ret;

	ret = 0;
	if ((*command)->builtin == builtin_echo)
	{
		// ret = echo((*command)->array);
		ret = echo(*command, *_env);
		if (ret == -1)
			(*command)->exit_status = 1;				//new
		exit((*command)->exit_status);
	}
	if ((*command)->builtin == builtin_export)
	{
		 execute_export(_env, command);
		 exit((*command)->exit_status);
	}
	if ((*command)->builtin == builtin_env)
	{
		env_array = env_ll_to_array(*_env);
		env(env_array);
		exit((*command)->exit_status);
	}
	
}

void			execute_builtin(t_command **command, t_env **_env)
{
	

    if ((*command)->builtin == builtin_cd)
        execute_cd(*command, _env);
    if ((*command)->builtin == builtin_pwd)
        execute_pwd(*command, *_env);

    // if ((*command)->builtin == builtin_export)
    //     execute_export(&env);
	if ((*command)->builtin == builtin_unset)
	 	execute_unset(*command, _env);
    if ((*command)->builtin == builtin_exit)
        execute_exit(*command);
}