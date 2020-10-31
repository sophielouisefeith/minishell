/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/10/31 20:47:25 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <dirent.h>
static char		*make_path_complete(char *patharray, char *tmp)
{
	char *new_str;
	char *new_str2;

	new_str = ft_strjoin(patharray, "/");
	new_str2 = ft_strjoin(new_str, tmp);
///LEAKS
	free(tmp);
	tmp = NULL;
	free(new_str);
	new_str = NULL;
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

char		*tmp_tolower(char *str)
{
	char	*tmp;
	int 	i;

	i = 0;
	tmp = ft_strdup(str);
	while (str[i] != '\0')
	{
		tmp[i] = ft_tolower(str[i]);
		i++;
	}
	return (tmp);
}

/*
** MOE:
	///	
	// if (str[0] != '$' && str[0] != '>' && str[0] != '<')	//LET OP: we mogen niet hier al erroren als $ nog niet expanded is //Ook niet bij > file
	// 	return (error_command(str));
	// else 
*/


char			*check_path(t_env *_env, char *str)
{
	struct dirent 	*next_entry;
	DIR				*folder;
	char			*path;
	char 			**patharray;
	int				i;
	char 			*tmp;

	i = 0;
	//printf("------------------------in check Path\n");
	path = search_node(_env, ft_strdup("PATH"));	//vanwege free in search node
	//printf("str[%s]\n", path);
	if (!path)
	{
		//printf("---------------------geen path\n");
		return (str);			// was return (errno = ENOENT, errno_error(str));
	}
	patharray = ft_split(path, ':');			//FREE
	if (!patharray)
		return (NULL);
	tmp = tmp_tolower(str);		//new
	while (patharray && patharray[i])
	{
		folder = opendir(patharray[i]);
		if (folder != 0)
		{
			while ((next_entry = readdir(folder)) != NULL)
			{
				if (ft_strcmp(next_entry->d_name, tmp) == 0) //was str
				{
					free(str);
					str = NULL;
					str = make_path_complete(patharray[i], tmp); //was str
					closedir(folder);
					///LEAKS
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
	if(str[0] == ';')
		printf(";\n");
	//if(ft_isalpha(str[0] )|| str[0] == ';')    //waarom blijft die verekte ; het niet doen omdat get_path verplaats is?
	//{	
		//return(error_path(2,str));
		//error_path(2,str);
		//return(NULL);
	//}
		
	// weer weg gehaald want anders gaat hij te vaak in error moet wel voor ; maar werkte nu ook niet meer waarschijnlijk door verplaatsing
	// if (str[0] != '$' && str[0] != '>' && str[0] != '<')	//LET OP: we mogen niet hier al erroren als $ nog niet expanded is //Ook niet bij > file
	// 	return (error_command(str));
	///LEAKS
	free(tmp);
	free_array(patharray);
	free(path);
	return (str);
}

/* Removed:
	///	
	// if (str[0] != '$' && str[0] != '>' && str[0] != '<')	//LET OP: we mogen niet hier al erroren als $ nog niet expanded is //Ook niet bij > file
	// 	return (error_command(str));
	// else 
*/