/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/10/30 17:50:10 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** error_command write to std_error fd[3]. 
TO DO:
bij andere errors ook doen?
*/


char				*error_path(int i, char *str)
{
	i =0;
		//printf("ik ben errno 2 en ik ben allene jrwekrjelj\n ");
		write(1, "bash: ", 6 );
		write(1, str, ft_strlen(str));
		write(1, ": ", 2 );
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
	//	return(0);
	return(str);
	
}

char				*error_command(char *str, int i, t_command *command)
{
	//printf("error_command\n");
	// printf("i[%d]\n", i);
	// printf("str[%s]\n", str);
	// if(g_exit_status == 127 || g_exit_status == 258 ||g_own_exit == 258  )  //wellicht nodig voor herhaling tegen gaan
	// {
	// 	set_exit_status();
	// 	return(str);
	// }
	write(1, "bash: ", 6 );
	if(!strncmp(str, ";", 1))
	{
		write(1, " syntax error near unexpected token `;'\n", 40);
		g_exit_status = 258;
		g_own_exit = 258;
		//i = 1;
		return(str);
	}
		write(3, str, ft_strlen(str));
		write(3, ": ", 2 );
		if(i == 3 || ((*command).builtin == executable))
		{
			printf(" je mot toch hier in als echo/  \n");
			write(1, "no such file or directory\n", 25);
		}
		else
			write(1, "command not found\n", 25);			//command not found (127)
		write(1, "\n", 1 );
		g_exit_status = 127;
		//g_own_exit = 127;		//? Quick and dirty solution voor $POEP. Naar kijken als we errormeldignen fixen
			return (str);
}

int					error(t_command *command)
{
	//printf("error\n");
	char 	*str_built;

	str_built = translate_builtin((command->builtin), NULL);
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

int				error_redirections(char c, int error_num, int i, char *line)
{
	line = "S";
	// printf("error_redirections\n");
	printf("i[%d]\n", i);
	// if(i > 1)
	// 	return(1);
	write(1, "bash: ", 9 );
	//printf("error[%d]\n", error_num);
	printf("i[%d]\n", g_exit_status );
	if (error_num == 1)
	{
		write(1, " syntax error near unexpected token  '", 35);
		//g_own_exit = 3;
		if (c == '\n' || c == '\0' || c == '#')
			write(1, "`newline'", 8);
		else
		{
			write(1, "`", 1);
			write(1, &c, 1);
		}
		write(1, "'\n", 2);
		g_exit_status = 258;   //	g_own_exit = 258; misschien nog er bij 
		return (5);  // dit is weer een herhaling geval 
	}
	write(1, &c, 1);
	if (error_num == 2)
		write(1, ": ambiguous redirect\n", 21);  // write(1, &c, 1); zat er eerst nog bij 
	if (error_num == 3)
		write(1, strerror(errno), ft_strlen(strerror(errno)));    //write(1, ": Is a directory\n", 17);		//errno 	EISDIR omschrijven naar errno_error?     //write(1, &c, 1);
	g_exit_status = 1;  // g_own_exit = 1; misschien nog er bij 
	return (1);
}

int				errno_error(char *str)
{
	//char str_2;
	// printf("ernno_error\n");
	// printf("errno1[%d]\n", errno);
	//int builtin_type;
	if(errno == 2)
	{
		write(1, "bash: ", 6 );
		write(1, str, ft_strlen(str));
		write(1, ": ", 2 );
		write(1, strerror(errno), ft_strlen(strerror(errno)));
		write(1, "\n", 1);
		return(3);
	}
	if(!strncmp(str, "<", ft_strlen(str)))   // dit is dus een andere exit status   test <jjy
	{
		g_exit_status = 1;
		g_own_exit = 127;
	}
	//str_2 = translate_builtin(executable, str);
	else if(executable)  // dirty executable solution 
	{
		printf("ex\n");
		//if(strncmp(str, "./", ft_strlen(str)))   ./ heeft dus nu weeer niet de juiste 
		errno = EISDIR;
		if(g_exit_status == 258)
			return(0);
		else
			set_exit_status();			//	./ hier zou  moeten komen de juiste status mee moeten krijgen waarom ?
	}
	// printf("errno2[%d]\n", errno);
	write(1, "bash: ", 6 );
//	if(!strncmp(".", str, 1))								// dit hoeft niet 
	//{
	//	not_part(str);
	//	return(str);
		// write(1, ".: filename argument required", 29);
		// write(1, "\n", 1);
		// write(1, ".: usage: . filename [arguments]", 32);
	//}
	
	{
		write(1, str, ft_strlen(str));
		write(1, ": ", 2 );
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	}
	write(1, "\n", 1);
	set_exit_status(); // ok dit heb ik er nu uitgehaald //NEW
	return (0);
}


char			*not_part(char *str) // behandeld nu ook qoutes
{
	printf("------------notpartofsubject\n");
	write(1, "bash: ", 6);
	write(1, str, ft_strlen(str));
	write(1, ": ", 2 );
	write(1, "multiline not part of subject\n", 29);
	write(1, "\n", 1);
	set_exit_status();
	
	return(NULL);
}


/*
** We willen g_own_exit hier behouden want we willen niet dat hij gaat executen.
*/

// char *error_qoute(char *str)
// {
// 	write(1, "bash: ", 6 );
// 	write(1,"unexpected EOF while looking for matching /"" ", 47);
// 	write(1, "\n", 1);
// 	write(1, "bash: syntax error: unexpected end of file", 43);
// 	write(1, "\n", 1);
// 	g_own_exit = 258;
// 	return(NULL);
// }

// void				*no_file(char *str, t_command *command) 
// {
	
// 	printf("exit[%d]\n", g_exit_status);
// 	if(g_exit_status == 258)
// 		return(str);
// 	// if(!strncmp(str, "./", 5))
// 	// {
// 	// 	errno = 21;
// 	// 	g_exit_status = 126;
// 		//return(str);
// 	//}
// 	//if(errno == EISDIR)
// 	//{
// 		//printf("ja\n");
// 		//write(3, "bash: ", 6 );
// 		//return(str);
// 	//}
// 	printf("errno[%d]\n", errno);
// 	//if(errno == EISI)
// 	//g_exit_status = 127;
// 	set_exit_status();
// 	// printf("errno[%d]\n", errno);  // kan zijn dat dit deel totaal overbodig is 
// 	write(3, "bash: ", 6 );
// 	write(3, str, ft_strlen(str));
// 	write(3, ": ", 2 );
// 	write(3, strerror(errno), ft_strlen(strerror(errno)));
// 	write(3, "\n", 1);
// 	return (str);
// }
