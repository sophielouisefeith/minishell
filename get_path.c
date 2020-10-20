/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/20 16:38:12 by maran         ########   odam.nl         */
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
		return (errno = ENOENT, errno_error(str));
	patharray = ft_split(path, ':');
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
	///	
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