/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/09/02 16:19:23 by msiemons      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** To do:
** - Korter maken
*/

static char		*make_path_complete(char *patharray, char *str)
{
	patharray = ft_strjoin(patharray, "/");
	patharray = ft_strjoin(patharray, str);
	return (patharray);
}

char			*check_path(t_env *_env, char *str)
{
	struct stat	buf;
	char 		**patharray;
	char		*current_dir;
	char		*path;
	int 		ret;
	int			i;

	i = 0;
	path = search_node(_env, "PATH");
	current_dir = search_node(_env, "PWD");
	if (!path)
		printf("No PATH in env");
	patharray = ft_split(path, ':');
	while (patharray && patharray[i])
	{
		ret = chdir(patharray[i]);
		if (ret == 0)
		{
			patharray[i] = make_path_complete(patharray[i], str);
			ret = stat(patharray[i], &buf);
			if (ret == 0)
			{
				chdir(current_dir);
				return (patharray[i]);
			}
		}
		i++;
	}
	return (NULL);
}
