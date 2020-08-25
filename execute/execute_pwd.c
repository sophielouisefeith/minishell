/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 12:46:44 by maran         #+#    #+#                 */
/*   Updated: 2020/08/25 15:00:34 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <limits.h>

int				execute_pwd(t_command *command, t_env *_env)
{
	char	buf[PATH_MAX];
	char	*path;

	path = getcwd(buf, sizeof(buf));
	if (path == NULL)
		perror("error");
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return(0);
}
