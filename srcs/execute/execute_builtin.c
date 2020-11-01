/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:15 by sfeith        #+#    #+#                 */
/*   Updated: 2020/11/01 13:37:49 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			execute_builtin(t_command **command, t_env **_env)
{
	int ret;

	ret = 0;
	if ((*command)->builtin == builtin_echo)
		ret = echo((*command)->array);
	if ((*command)->builtin == builtin_cd)
		ret = execute_cd(*command, _env);
	if ((*command)->builtin == builtin_pwd)
		ret = execute_pwd(*command);
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
