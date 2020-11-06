/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/11/06 18:23:53 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>

static char		*clean_exit_check_path(char *tmp, char *new_str, char *str)
{
	free(tmp);
	tmp = NULL;
	if (new_str)
	{
		free(str);
		str = NULL;
		return (new_str);
	}
	return (str);
}

static char		*make_path_complete(char *patharray, char *tmp)
{
	char		*new_str;
	char		*new_str2;

	new_str = ft_strjoin(patharray, "/");
	new_str2 = ft_strjoin(new_str, tmp);
	free(new_str);
	new_str = NULL;
	return (new_str2);
}

static char		*check_directories(char *tmp, char *patharray_i, DIR *folder)
{
	struct dirent	*next_entry;
	char			*new_str;

	while ((next_entry = readdir(folder)) != NULL)
	{
		if (ft_strcmp(next_entry->d_name, tmp) == 0)
		{
			new_str = make_path_complete(patharray_i, tmp);
			closedir(folder);
			return (new_str);
		}
	}
	return (NULL);
}

/*
** 1. Get the PATH variable out of _env
** 2. Save the PATH values in seperate strings
** 3. Try to open every individual directory
** 4. Read every entry of the directory and compare to entered string
** 5. If entry is equal complete the entered path by
** adding the path of directory
*/

static char		*check_path(char *str, char *path)
{
	DIR			*folder;
	char		**patharray;
	char		*new_str;
	char		*tmp;
	int			i;

	i = 0;
	patharray = ft_split(path, ':');
	if (!patharray)
		return (NULL);
	tmp = tmp_tolower(str);
	while (patharray && patharray[i])
	{
		folder = opendir(patharray[i]);
		if (folder != 0)
		{
			new_str = check_directories(tmp, patharray[i], folder);
			if (new_str)
				break ;
			closedir(folder);
		}
		i++;
	}
	free_array(patharray);
	return (clean_exit_check_path(tmp, new_str, str));
}

void			complete_path(t_command **command, t_env *envb)
{
	char		*str_before;
	char		*tmp;
	char		*path;

	str_before = NULL;
	if ((*command)->builtin == builtin_no && (*command)->array)
	{
		path = search_node(envb, ft_strdup("PATH"));
		if (path)
		{
			str_before = ft_strdup((*command)->array[0]);
			tmp = strdup_and_free(&(*command)->array[0]);
			(*command)->array[0] = check_path(tmp, path);
			if ((*command)->array[0] == NULL)
				error_command((*command)->array[0], 1, *command);
			free(path);
			if (!ft_strcmp(str_before, (*command)->array[0]))
				(*command)->builtin = builtin_no_com;
			free(str_before);
			return ;
		}
		(*command)->builtin = executable;
	}
}
