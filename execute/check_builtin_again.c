/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_builtin_again.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 17:31:13 by maran         #+#    #+#                 */
/*   Updated: 2020/10/12 10:58:21 by maran         ########   odam.nl         */
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
*/

void				check_builtin_again(t_command **command, t_env *_env, int y)
{
	if ((*command)->builtin == builtin_no_com && y == 0)
	{
		while ((*command)->array && (*command)->array[y + 1])
		{
			(*command)->array[0] = ft_strjoin((*command)->array[y], " ");
			(*command)->array[0] = ft_strjoin((*command)->array[0], (*command)->array[y + 1]);
			y++;
		}
		lexer_parser_executer((*command)->array[0], 0, &_env);
	}
}
