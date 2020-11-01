/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/08/05 12:28:48 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/11/01 17:19:31 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				error(t_command *command)
{
	char	*str_built;

	str_built = translate_builtin((command->builtin), NULL);
	write(1, "bash: ", 6);
	write(1, str_built, ft_strlen(str_built));
	write(1, "'", 1);
	write(1, command->array[0], ft_strlen(command->array[0]));
	write(1, "'", 1);
	write(1, ": ", 2);
	if (!strncmp(str_built, "export", 1) || !strncmp(str_built, "unset", 1))
	{
		write(1, "not a valid identifier", 22);
		g_exit_status = 1;
	}
	else
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
	return (-1);
}

static int		check_input_redirection(int i, char *line)
{
	int		count;

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
		flag = check_input_redirection(i, line);
	if (c == ';' && line[i + 1] == ';')
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
	g_exit_status = 258;
	g_own_exit = 3;
	return (5);
}

int				error_redirections(char c, int error_num, int i, char *line)
{
	(void)i;
	(void)line;
	write(1, "bash: ", 9);
	write(1, &c, 1);
	if (error_num == 2)
		write(1, ": ambiguous redirect\n", 21);
	if (error_num == 3)
		write(1, strerror(errno), ft_strlen(strerror(errno)));
	g_exit_status = 1;
	g_own_exit = 1;
	return (1);
}

int				errno_error(char *str, t_command *command)
{
	if ((*command).builtin == executable)
	{
		errno = EISDIR;
		if (g_exit_status == 258)
			return (0);
		else
			set_exit_status();
	}
	write(1, "bash: ", 6);
	write(1, str, ft_strlen(str));
	write(1, ": ", 2);
	write(1, strerror(errno), ft_strlen(strerror(errno)));
	write(1, "\n", 1);
	set_exit_status();
	if (errno == 2)
	{
		g_exit_status = 1;
		return (3);
	}
	return (0);
}
