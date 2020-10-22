/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/22 17:18:58 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static char		*make_path_complete(char *patharray, char *str)
{
	char *new_str;
	char *new_str2;

	new_str = ft_strjoin(patharray, "/");
	new_str2 = ft_strjoin(new_str, str);
///LEAKS
	free(str);
	str = NULL;
	free(new_str);
	new_str = NULL;
	free(patharray);
	patharray = NULL;
///
	return (new_str2);
}

/*
** Methode met open, read en closedir:
** 1. Get the PATH variable out of _env
** 2. Save the PATH values in seperate strings
** 3. Try to open every individual directory
** 4. Read every entry of the directory and compare to entered string
** 5. If entry is equal complete the entered path by adding the path of directory
*/

char			*check_path(t_env *_env, char *str)
{
	struct dirent 	*next_entry;
	DIR				*folder;
	char			*path;
	char 			**patharray;
	int				i;
	
	i = 0;
	path = search_node(_env, ft_strdup("PATH"));	//vanwege free in search node
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
					///LEAKS
					str = ft_strdup(patharray[i]);
					free_array(patharray);
					free(path);
					///
					return (str);
				}
			}
			closedir(folder);
		}
		i++;
	}
	///LEAKS
	free_array(patharray);
	free(path);
	///	
	if (str[0] != '$' && str[0] != '>' && str[0] != '<')	//LET OP: we mogen niet hier al erroren als $ nog niet expanded is //Ook niet bij > file
		return (error_command(str));
	else 
		return (str);
}
