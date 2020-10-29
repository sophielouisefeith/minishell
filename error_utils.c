/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error_utils.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/27 14:45:39 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/29 12:26:10 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char 			*translate_builtin(int b)
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

int 			malloc_fail()
{ 
	if(errno == ENOMEM)
	{
		write(1, "bash: ", 6 );
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		exit(1);	
	}
	return(errno);
}

void				set_exit_status(void)
{
	if (errno == ENOENT)	// "No such file or directory\n"
	{
		g_exit_status = 127;
		g_own_exit = 127;
	}
	if (errno == EACCES || errno == EISDIR )    //Permission denied. 
	{
		g_exit_status = 126;
		// g_own_exit = 126;
	}
	else
	{
		g_exit_status = 1;
		// g_own_exit = 1;
	}
	return ;
}