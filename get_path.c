/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/11/01 12:04:26 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>		//Waar is deze voor?

static char		*make_path_complete(char *patharray, char *tmp)
{
	char *new_str;
	char *new_str2;

	new_str = ft_strjoin(patharray, "/");
	new_str2 = ft_strjoin(new_str, tmp);
	free(tmp);
	tmp = NULL;
	free(new_str);
	new_str = NULL;
	return (new_str2);
}

/*
** 1. Get the PATH variable out of _env
** 2. Save the PATH values in seperate strings
** 3. Try to open every individual directory
** 4. Read every entry of the directory and compare to entered string
** 5. If entry is equal complete the entered path by adding the path of directory
*/

char			*tmp_tolower(char *str)
{
	char	*tmp;
	int		i;

	i = 0;
	tmp = ft_strdup(str);
	while (str[i] != '\0')
	{
		tmp[i] = ft_tolower(str[i]);
		i++;
	}
	return (tmp);
}

// static char			*proceed_path(DIR *folder, int i, char *patharray,
// char *tmp, char *str)
// {
// 	free(str);
// 	str = NULL;
// 	str = make_path_complete(&patharray[i], tmp);
// 	closedir(folder);
// 	// free(tmp);
// 	free_array(&patharray);
// 	// free(path);
// 	free(tmp);
// 	return (str);
// }

// static char 		*while_path(char **patharray, int i, char *tmp, char *str, char *path)
// {
// 	DIR				*folder;
// 	struct dirent	*next_entry;

// 	while (*patharray && *patharray[i])
// 	{
// 		folder = opendir(patharray[i]);
// 		if (folder != 0)
// 		{
// 			while ((next_entry = readdir(folder)) != NULL)
// 			{
// 				if (ft_strcmp(next_entry->d_name, tmp) == 0)
// 				{
// 					str = proceed_path(folder, i, *patharray, tmp, str);
// 					free(path);
// 					free(tmp);
// 					return (str);
// 				}
// 			}
// 			closedir(folder);
// 		}
// 		i++;
// 	}
// 	free(tmp);
// 	free_array(patharray);
// 	free(path);
// 	return (str);
// }


char			*check_path(t_env *_env, char *str)
{
	struct dirent 	*next_entry;
	DIR				*folder;
	char			*path;
	char 			**patharray;
	int				i;
	char 			*tmp;

	i = 0;
	path = search_node(_env, ft_strdup("PATH"));
	if (!path)
		return (str);
	patharray = ft_split(path, ':');
	if (!patharray)
		return (NULL);
	tmp = tmp_tolower(str);
	while (patharray && patharray[i])
	{
		folder = opendir(patharray[i]);
		if (folder != 0)
		{
			while ((next_entry = readdir(folder)) != NULL)
			{
				if (ft_strcmp(next_entry->d_name, tmp) == 0)
				{
					free(str);
					str = NULL;
					str = make_path_complete(patharray[i], tmp);
					closedir(folder);
					free_array(patharray);
					free(path);
					return (str);
				}
			}
			closedir(folder);
		}
		i++;
	}
	free(tmp);
	free_array(patharray);
	free(path);
	return (str);
}
