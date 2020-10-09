/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/10/06 10:47:08 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char 			*translate_builtin(int b)
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
	// else
    //     return (builtin_no);
	return (NULL);
}


char				*error_command(char *str)
{
	
	write(1, "bash: ", 6 );
	if(!strncmp(str, ";", 1))
	{
		write(1, " syntax error near unexpected token `;'\n", 40);
		g_exit_status = 258;
		return(str);
	}
	write(1, str, ft_strlen(str));
	write(1, ": ", 2 );
	write(1, "command not found\n", 18);
	g_exit_status = 127;
	return (str);
}

int					error(t_command *command)
{
	char 	*str_built;

	str_built= translate_builtin((command->builtin));
	write(1, "bash: ", 6 );
	write(1, str_built, ft_strlen(str_built));
	write(1, "'", 1);
	write(1, command->array[0], ft_strlen(command->array[0]));
	write(1, "'", 1);
	write(1, ": ", 2 );
	if(!strncmp(str_built, "export", 1))
	{
		write(1, "not a valid identifier", 22);
		//g_exit_status = 1;
	}
	else
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1 );
	return (-1);
}

