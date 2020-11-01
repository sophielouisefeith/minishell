/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 14:45:39 by sfeith        #+#    #+#                 */
/*   Updated: 2020/11/01 12:10:49 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char						*translate_builtin(int b, char *str)
{
	if (b == builtin_echo)
		return ("echo: ");
	if (b == builtin_cd)
		return ("cd: ");
	if (b == builtin_pwd)
		return ("pwd: ");
	if (b == builtin_export)
		return ("export: ");
	if (b == builtin_unset)
		return ("unset: ");
	if (b == builtin_env)
		return ("env: ");
	if (b == builtin_exit)
		return ("exit: ");
	if (b == executable)
	{
		if (!ft_strncmp(str, "/", 1))
			return ("/");
		if (!ft_strncmp(str, "../", 3))
			return ("../");
		if (!ft_strncmp(str, "./", 3))
			return ("./");
	}
	return (NULL);
}

int							malloc_fail(void)
{
	write(1, "bash: ", 6);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	exit(1);
}

void						set_exit_status(void)
{
	if (errno == ENOENT)
	{
		g_exit_status = 127;
		g_own_exit = 127;
		return ;
	}
	if (errno == EACCES || errno == EISDIR)
		g_exit_status = 126;
	else
		g_exit_status = 1;
	return ;
}

char				*error_command(char *str, int i, t_command *command)
{
	write(1, "bash: ", 6);
	if (!strncmp(str, ";", 1))
	{
		write(1, " syntax error near unexpected token `;'\n", 40);
		g_exit_status = 258;
		return (str);
	}
	write(3, str, ft_strlen(str));
	write(3, ": ", 2);
	if (i == 3 || ((*command).builtin == executable))
		write(1, "no such file or directory\n", 25);
	else
		write(1, "command not found\n", 17);
	write(1, "\n", 1);
	g_exit_status = 127;
	g_own_exit = 127;
	return (str);
}
