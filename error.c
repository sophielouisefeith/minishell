/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/10/26 11:17:40 by maran         ########   odam.nl         */
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

/*
** error_command write to std_error fd[3]. 
TO DO:
bij andere errors ook doen?
*/


char				*error_command(char *str)
{
		write(3, "bash: ", 6 );
		if(!strncmp(str, ";", 1))
		{
			write(3, " syntax error near unexpected token `;'\n", 40);
			g_exit_status = 258;
			return(str);
		}
		write(3, str, ft_strlen(str));
		write(3, ": ", 2 );
		write(3, "command not found\n", 18);			//No such file or directory (127)
		g_exit_status = 127;
		// g_own_exit = 127;		//? Quick and dirty solution voor $POEP. Naar kijken als we errormeldignen fixen
			return (str);
}

int					error(t_command *command)
{
	char 	*str_built;

	str_built = translate_builtin((command->builtin));
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
	//int 	num;
	//printf("kom je hier dan 1 \n");
	write(1, "bash: ", 6 );
	if (error_num == 1)
	{
		write(1, "syntax error near unexpected token '", 35);
		if (c == '\n' || c == '\0' || c == '#')
			write(1, "' newline", 8);
		else
			write(1, &c, 1);
		write(1, "'\n", 2);
		g_exit_status = 258;
		// g_own_exit = 258;
		return (1);
	}
	write(1, &c, 1);
	if (error_num == 2)
	{
		// write(1, &c, 1);
		write(1, ": ambiguous redirect\n", 21);
	}
	if (error_num == 3)
	{
		//write(1, &c, 1);
		write(1, ": Is a directory\n", 17);		//errno 	EISDIR --> omschrijven naar errno_error?
	}
	g_exit_status = 1;
	// g_own_exit = 1;
	return (1);
}


// MARAN ERRORS:

void				set_exit_status(void)
{
	if (errno == ENOENT)	// "No such file or directory\n"
	{
		g_exit_status = 127;
		// g_own_exit = 127;
	}
	if (errno == EACCES)    //Permission denied. 
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


int 			malloc_fail(int er)
{ 
	if(errno == ENOMEM)
	{
		write(1, "bash: ", 6 );
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		//write(1, "cannot allocate memory ", 32 ); // dit ook met eern strerrr opschrijvven
		// g_own_exit = 1;
		exit(1);
		
	}
	return(errno);
}

void				*errno_error(char *str, t_command *command)
{
	int builtin_type;
	if(executable)  // dirty executable solution 
	{
		errno = 21;
		g_exit_status = 126;
		// g_own_exit = 126;
	}
	write(1, "bash: ", 6 );
	write(1, str, ft_strlen(str));
	write(1, ": ", 2 );
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
	set_exit_status();
	return (str);
}


/*
** We willen g_own_exit hier behouden want we willen niet dat hij gaat executen.
*/

char *error_qoute(char *str)
{
	write(1, "bash: ", 6 );
	write(1,"unexpected EOF while looking for matching /"" ", 47);
	write(1, "\n", 1);
	write(1, "bash: syntax error: unexpected end of file", 43);
	write(1, "\n", 1);
	g_own_exit = 258;
	return(NULL);
}

char			*error_parameter(char *str)
{
	write(1, "bash: ", 6);
	write(1, str, ft_strlen(str));
	write(1, ": ", 2 );
	write(1, "Not part of the subject\n", 24);
	set_exit_status();
	return(NULL);
}
