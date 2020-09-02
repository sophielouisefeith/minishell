/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_path.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/09/02 11:52:10 by sfeith        #+#    #+#                 */
/*   Updated: 2020/09/02 13:21:04 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int			check_path(t_env **_env, t_lexer **sort)
{
	char	*path;

	path = (*sort)->str;
	printf("-----------------------------------we gaan een path zoeken\n");

	printf("str[%s]\n", path);
	while(_env)
	{
		search_node
		execve
	}
	// in je env zit een bin opgeslagen dus zoek die bin ga daar in en dan loopen of het strincmp met *sort->str. dan ben je een
	//path  en slaan we je op in filenname 
    // else // er is geen path en geen builtin dus dan moeten we een foutmelding krijgen
	// {
		
	// }
	
	return(0);
}


// eeerste node als path opslaan en alles wat er na komt opslaan in een argv  **array opties zoals -la 