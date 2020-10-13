/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/10/13 12:21:39 by SophieLouis   ########   odam.nl         */
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
	write(1, "command not found\n", 18);			//No such file or directory (127)
	g_exit_status = 127;
	g_own_exit = 127;		//? Quick and dirty solution voor $POEP. Naar kijken als we errormeldignen fixen
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

/* 
** Quick and dirty solution. Afhankelijk van hoe we errors gaan handelen.
** Nu returnt 1 omdat hij in token[token_redirection] terecht komt in save operator

** TO DO:
	- Nu komt hij bij ls >>>>>>>>>>> file nog 5 x in de foutmelding. Eigenlijk moet hij er naar 1 error al uitklappen.
	Heeft met onze error structuur te maken die nog niet werkt.
*/

int				error_redirections(char c, int error_num)
{
	write(1, "bash: ", 6 );
	if (error_num == 1)
	{
		write(1, "syntax error near unexpected token '", 36);
		write(1, &c, 1);
		write(1, "'\n", 2);
		g_exit_status = 258;
		g_own_exit = 258;
		return (1);
	}
	if (error_num == 2)
	{
		write(1, &c, 1);
		write(1, ": ambiguous redirect\n", 22);
	}
	if (error_num == 3)
	{
		write(1, &c, 1);
		write(1, ": Is a directory\n", 18);
	}
	g_exit_status = 1;
	g_own_exit = 1;
	return (1);
}


// Misschien beter om met error_nums te werken, nu veel overlap de hele tijd.

char				*error_no_path(char *str)
{
	write(1, "bash: ", 6 );
	write(1, str, ft_strlen(str));
	write(1, ": ", 2 );
	write(1, "No such file or directory\n", 27);
	g_exit_status = 127;
	g_own_exit = 127;
	return (str);
}

char			*error_parameter(char *str)
{
	write(1, "bash: ", 6 );
	write(1, str, ft_strlen(str));
	write(1, ": ", 2 );
	write(1, "Not part of the subject\n", 27);
	return(NULL);
	
}