/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_builtin.c                                  :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/24 14:13:15 by sfeith        #+#    #+#                 */
/*   Updated: 2020/11/06 16:58:18 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			execute_builtin(t_command **command, t_env **envb)
{
	int ret;

	ret = 0;
	if ((*command)->builtin == builtin_echo)
		ret = echo((*command)->array);
	if ((*command)->builtin == builtin_cd)
		ret = execute_cd(*command, envb);
	if ((*command)->builtin == builtin_pwd)
		ret = execute_pwd(*command);
	if ((*command)->builtin == builtin_export)
		ret = execute_export(envb, command);
	if ((*command)->builtin == builtin_unset)
		ret = execute_unset(*command, envb);
	if ((*command)->builtin == builtin_env)
		ret = env(*envb);
	if ((*command)->builtin == builtin_exit)
		execute_exit(*command);
	if (ret == -1 && (*command)->builtin != builtin_exit)
		g_exit_status = 1;
	else if (ret != -1 && (*command)->builtin != builtin_exit)
		g_exit_status = 0;
}
