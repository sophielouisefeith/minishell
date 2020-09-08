/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/09/08 16:34:07 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char 			*translate_builtin(int b)
{   
    if (1)
		return ("echo: ");
	if (2)
		return ("cd: ");
    if (3)
		return ("pwd: ");
	if (4)
		return ("export: ");
    if (5)
		return ("unset: ");
	if (6)
		return ("env: ");
  	if (7)
		return ("exit: ");
	// else
    //     return (builtin_no);
}

char					*error_command(char *str)
{
	g_exit_status = 127;
	
	write(1, "bash: ", 6 );
	write(1, str, ft_strlen(str));
	write(1, ": ", 2 );
	write(1, "command not found\n", 18);
	return (str);
}

int					error(t_command *command)
{

	
	char 	*str_built;

	str_built= translate_builtin((command->builtin));

	write(1, "bash: ", 6 );
	write(1, str_built, ft_strlen(str_built));
	write(1, command->array[0], ft_strlen(command->array[0]));
	write(1, ": ", 2 );
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1 );
	
	return (-1);
}

