/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   execute_pwd.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/24 12:46:44 by maran         #+#    #+#                 */
/*   Updated: 2020/10/30 17:42:40 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <limits.h>

int				execute_pwd(void)
{
	//printf("--------- we zijn in pwd\n");
	char	buf[PATH_MAX];
	char	*path;

	path = getcwd(buf, sizeof(buf));
	if (path == NULL)
	{
		strerror(errno);
		return (-1);
	}
	write(1, path, ft_strlen(path));
	write(1, "\n", 1);
	return (0);
}
