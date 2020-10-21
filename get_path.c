/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/21 13:10:38 by SophieLouis   ########   odam.nl         */
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
		return (errno = ENOENT, errno_error(str, 0));
	patharray = ft_split(path, ':');			//FREE
	if(!patharray)
		return(NULL);
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
	if (str[0] != '$' && str[0] != '>' && str[0] != '<')
		return (error_command(str)); //LET OP: we mogen niet hier al erroren als $ nog niet expanded is //Ook niet bij > file
	else 
		return (str);
}
