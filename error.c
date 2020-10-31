/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/10/31 20:32:28 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** error_command write to std_error fd[3]. 
TO DO:
bij andere errors ook doen?
*/
/* 
** Quick and dirty solution. Afhankelijk van hoe we errors gaan handelen.
** Nu returnt 1 omdat hij in token[token_redirection] terecht komt in save operator

** TO DO:
	- Nu komt hij bij ls >>>>>>>>>>> file nog 5 x in de foutmelding. Eigenlijk moet hij er naar 1 error al uitklappen.
	Heeft met onze error structuur te maken die nog niet werkt.
*/

int					error(t_command *command)
{
	char 	*str_built;

	str_built = translate_builtin((command->builtin), NULL);
	write(1, "bash: ", 6 );
	write(1, str_built, ft_strlen(str_built));
	write(1, "'", 1);
	write(1, command->array[0], ft_strlen(command->array[0]));
	write(1, "'", 1);
	write(1, ": ", 2 );
	if(!strncmp(str_built, "export", 1) || !strncmp(str_built, "unset", 1))
	{
		write(1, "not a valid identifier", 22);
		g_exit_status = 1;
	}
	else
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1 );
	return (-1);
}

static int			check_input_redirection(int i, char *line)
{
	
	int 		count;

	count = 0;
	while (line[i] == '<')
		i++;
	if (i <= 3)
		return (0);
	else if (i == 4)
		return (1);
	else if (i == 5)
		return (2);
	else
		return (3);
		
}


int				error_redi_one(char c, int i, char *line)
{
	int flag;

	flag = 1;
	write(1, "bash: syntax error near unexpected token `", 42);
	if (c == '<' || c == '>')
		flag = check_input_redirection(i, line);				//M: ik vind wel ver gaan. Maar werkt wel.
	if (c == ';' && line[i + 1] == ';')							//M: same ik vind ver gaan.
		flag = 2;
	if (c == '\n' || c == '\0' || c == '#')
		flag = 0;
	if (flag == 0)
		write(1, "newline", 8);
	else
	{
		while (flag)
		{
			write(1, &c, 1);
			flag--; 
		}
	}
	write(1, "'\n", 2);
	g_exit_status = 258;   	//	g_own_exit = 258; misschien nog er bij 			[SOP NAAR KIJKEN]
	return (5);  			// dit is weer een herhaling geval 
	// //g_own_exit = 3;
}



int				error_redirections(char c, int error_num, int i, char *line)
{
	(void)i;
	(void)line;
	write(1, "bash: ", 9 );
	write(1, &c, 1);
	if (error_num == 2)
		write(1, ": ambiguous redirect\n", 21);  // write(1, &c, 1); zat er eerst nog bij  zit hier de juiste exit status 
	if (error_num == 3)
		write(1, strerror(errno), ft_strlen(strerror(errno)));    //write(1, ": Is a directory\n", 17);		//errno 	EISDIR omschrijven naar errno_error?     //write(1, &c, 1);
	g_exit_status = 1;  
	g_own_exit = 1; //misschien nog er bij 
	return (1);
}


int				errno_error(char *str, t_command *command)
{
	
	if((*command).builtin == executable) 
	{
		printf("ex\n");
		errno = EISDIR;
		if(g_exit_status == 258)
			return(0);
		else
			set_exit_status();		
	}
	write(1, "bash: ", 6 );
	write(1, str, ft_strlen(str));
	write(1, ": ", 2 );
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
	set_exit_status(); // ok dit heb ik er nu uitgehaald //NEW
	if (errno == 2)
	{
		g_exit_status = 1;;
		return(3);
	}
	return (0);
}


char			*not_part(char *str) // behandeld nu ook qoutes
{
	write(1, "bash: ", 6);
	write(1, str, ft_strlen(str));
	write(1, ": ", 2 );
	write(1, "multiline not part of subject\n", 29);
	write(1, "\n", 1);
	g_exit_status =258;
	//set_exit_status();
	
	return(NULL);
}
