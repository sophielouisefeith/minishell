/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/12 09:14:33 by SophieLouis   ########   odam.nl         */
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
		return (error_no_path(str));
	patharray = ft_split(path, ':');			//FREE
	while (patharray && patharray[i])
	{
		//printf("----path array[%s]\n", patharray[i] );
		folder = opendir(patharray[i]);
		if (folder != 0)
		{
			//printf("----path array[%s]\n", patharray[i] );
			while ((next_entry = readdir(folder)) != NULL)
			{
				if (ft_strcmp(next_entry->d_name, str) == 0)
				{
					patharray[i] = make_path_complete(patharray[i], str);
					closedir(folder);
					// printf("----path array[%s]\n", patharray[i] );
					return (patharray[i]);
				}
			}
			closedir(folder);
		}
		i++;
	}
	if (str[0] != '$' && str[0] != '>' && str[0] != '<')										//LET OP: we mogen niet hier al erroren als $ nog niet expanded is //Ook niet bij > file
		return (error_command(str));
	else 
		return (str);
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