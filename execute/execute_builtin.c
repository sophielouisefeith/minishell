/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:15 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/29 09:42:58 by maran         ########   odam.nl         */
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
unset: The return status is zero unless a name is readonly or does not exist.
env: The env utility exits 0 on success, and >0 if an error occurs.  An exit status of 126 indicates that utility was found, but could not be executed.  An exit status of 127 indicates that utility could not be found.
-----------

Simple shell command: echo
*/

/*
** Echo: write returns -1 when error + errno is set. Check
** Cd: chdir returns -1 if not succesful + errno is set. Check
** Pwd: getcwd NULL als onsuccesvol (pwd < 0) + errno is set. Check
** Export: 
** Unset: -1 if not a valid identifier, invalid option ommit, does not exit still returns 0. Check?
** Env: write returns -1 when error. Check?
** Export: -1 wanneer invalid identifier. Check? 
** Exit: ------- werkt anders qua exit_status. Zie functie.
*/


/*
** LET OP: PLaats van execute_exit belangrijk! niet boven:
if (ret == -1)
		g_exit_status = 1;
	else
		g_exit_status = 0;
	// printf("In execute_builtin: [%p][%s]   [%p]\n", (*command)->array[0], (*command)->array[0], &(*command)->array[0]);
*/

void			execute_builtin(t_command **command, t_env **_env)
{
	int ret;

	ret = 0;
	if ((*command)->builtin == builtin_echo)
		ret = echo((*command)->array);
    if ((*command)->builtin == builtin_cd)
        ret = execute_cd(*command, _env);
    if ((*command)->builtin == builtin_pwd)
        ret = execute_pwd();
	if ((*command)->builtin == builtin_export)
		ret = execute_export(_env, command);
	if ((*command)->builtin == builtin_unset)
	 	ret = execute_unset(*command, _env);
	if ((*command)->builtin == builtin_env)
		ret = env(*_env);
	if ((*command)->builtin == builtin_exit)
		execute_exit(*command);
	if (ret == -1 && (*command)->builtin != builtin_exit)
		g_exit_status = 1;
	else if (ret != -1 && (*command)->builtin != builtin_exit)
		g_exit_status = 0;
}
