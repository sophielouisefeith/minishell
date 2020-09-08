/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/09/08 21:15:39 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
 
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

/*
** Methode met open, read en closedir:
*/

char			*check_path(t_env *_env, char *str)
{
	struct dirent 	*next_entry;
	DIR				*folder;
	char			*path;
	char 			**patharray;
	int				i;
	
	i = 0;
	path = search_node(_env, "PATH");
	if (!path)
		printf("No PATH in env\n");
	patharray = ft_split(path, ':');			//FREE
	while (patharray && patharray[i])
	{
		folder = opendir(patharray[i]);
		if (folder != 0)
		{
			while ((next_entry = readdir(folder)) != NULL)
			{
				if (ft_strcmp(next_entry->d_name, str) == 0)
				{
					patharray[i] = make_path_complete(patharray[i], str);
					closedir(folder);
					return (patharray[i]);
				}
			}
			closedir(folder);
		}
		i++;
	}
	return (error_command(str)); 							//Was NULL
	// return (NULL);
}

/*
** Methode met Stat:
*/

// char			*check_path(t_env *_env, char *str)
// {
// 	struct stat	buf;
// 	char 		**patharray;
// 	char		*current_dir;
// 	char		*path;
// 	int 		ret;
// 	int			i;

// 	i = 0;
// 	path = search_node(_env, "PATH");
// 	current_dir = search_node(_env, "PWD");
// 	if (!path)
// 		printf("No PATH in env");
// 	patharray = ft_split(path, ':');
// 	while (patharray && patharray[i])
// 	{
// 		ret = chdir(patharray[i]);
// 		if (ret == 0)
// 		{
// 			patharray[i] = make_path_complete(patharray[i], str);
// 			ret = stat(patharray[i], &buf);
// 			if (ret == 0)
// 			{
// 				chdir(current_dir);
// 				return (patharray[i]);
// 			}
// 		}
// 		i++;
// 	}
// 	return (NULL);
// }