/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   pwd.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 12:46:44 by maran         #+#    #+#                 */
/*   Updated: 2020/11/03 22:11:31 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

void			error_pwd_unset(char *str, char *path)
{
	if (str[0] == '-' && str[1] != 'P'
	&& str[1] != 'L' && str[1] != '\0' && \
	!ft_strcmp(path, "unset"))
	{
		write(1, "bash: pwd: ", 11);
		write(1, &str[1], 1);
		write(1, " invalid option", 15);
		write(1, "\n", 1);
		write(1, "pwd: usage: pwd [-LP]", 21);
	}
	else
		write(1, path, ft_strlen(path));
}

int				execute_pwd(t_command *command)
{
	char	buf[PATH_MAX];
	char	*path;

	path = getcwd(buf, sizeof(buf));
	if (path == NULL)
	{
		strerror(errno);
		return (-1);
	}
	if ((command)->array)
		error_pwd_unset((*command).array[0], path);
	else
		write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (0);
}
