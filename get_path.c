/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/09/02 14:36:39 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** wellicht tmps gebruiken 
** To do:
** - Testen of het in alle gevallen goed gaat door op -1 te beginnen.
*/

static char	make_path_complete(char *patharray, char *str)
{
	

	printf("patharray[%s]\n", patharray);
	printf("str[%s]\n", str);

	patharray = ft_strjoin(patharray, "/");
	printf("ater join[%s]\n", patharray);
	patharray = ft_strjoin(patharray, str);
	printf("join str[%s]\n", patharray);
	/// str erachter plakken
	return(0);
}

int			check_path(t_env *_env, char *str)
{
	char		*path;
	char 		**patharray;
	struct stat  *safe;
	int			i;
	
	
	printf("str[%s]\n", path);
	path = search_node(_env, "PATH");
	if(!path)
		printf("-----------------------------------no PATH in env");
	patharray= ft_split(path, ':');
	printf("arraypath[%s]\n[%s]\n", patharray[0], patharray[1]);
	while(patharray && patharray[i])
	{
		chdir(patharray[i]);
		stat(patharray[i], safe);
		make_path_complete(patharray[i], str);
		i++;
	}
	// in je env zit een bin opgeslagen dus zoek die bin ga daar in en dan loopen of het strincmp met *sort->str. dan ben je een
	//path  en slaan we je op in filenname 
    // else // er is geen path en geen builtin dus dan moeten we een foutmelding krijgen
	// {
		
	// }
	
	return(0);
}


// eeerste node als path opslaan en alles wat er na komt opslaan in een argv  **array opties zoals -la 