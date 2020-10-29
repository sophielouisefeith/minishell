/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_builtin_again.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 17:31:13 by maran         #+#    #+#                 */
/*   Updated: 2020/10/29 12:08:07 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Scary;  gaat  dit in alle volgordes goed ? Ook eng met leaks. IF LEAKS KIJK ZEKER HIER!!

Werkt niet:
export POEP="ls -la"
echo hoi | $POEP

export POEP="grep main"
ls > x1 ; cat x1 | $POEP

TO DO: 
$POEP			--> bash: $POEP: command not found 			-->  foutmelding weghalen
hallo $POEP 	--> bash: hallo: command not found  		--> dan er al uit klappen! Behalve als eerste woord begint met$	
------
TO DO:
	- Wat als y geen 0, gaat het dan goed. Welke gevallen is dit?		MEER TESTEN (of vanzelf achterkomen.)
------
** When there is a $ sign. And there is no known command yet the _env variable should be checked on comments inside the variable.
** >$ export LS="ls -la" 
** >$ $LS

PAS OP: 
(*command)->array[0][0] != '$' toegevoegd v.w. $"poep" --> Kan niet overzien of dit alles dekt, te beperkt? 

//[0] != '$' toegevoegd v.w. $"poep"
*/



/*
** MOE:
 && (*command)->array[y] != NULL toegevoegd
*/


void				check_builtin_again(t_command **command, t_env *_env, int y)
{
	char *new_str;
	char *tmp;
	char *y_space;

	if ((*command)->builtin == builtin_no_com && y == 0 && (*command)->array[y] != NULL)
	{
		new_str = ft_strdup("");
		while ((*command)->array && (*command)->array[y])
		{
			y_space = ft_strjoin((*command)->array[y], " ");
			tmp = ft_strjoin(new_str, y_space);
			free(new_str);
			new_str = ft_strdup(tmp);
			free(y_space);
			free(tmp);
			y++;
		}
		if (new_str && new_str[0] != '$')
		{
			lexer_parser_executer(new_str, 0, &_env);
			g_own_exit= 999;
			free(new_str);
		}
	}
}
