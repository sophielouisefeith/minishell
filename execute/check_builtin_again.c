/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_builtin_again.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 17:31:13 by maran         #+#    #+#                 */
/*   Updated: 2020/10/08 15:36:27 by maran         ########   odam.nl         */
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
** When there is a $ sign. And there is no known command yet the _env variable should be checked on comments inside the variable.
** >$ export LS="ls -la" 
** >$ $LS
*/

void				check_builtin_again(t_command **command, t_env *_env, int y)
{
	if ((*command)->builtin == builtin_no_com)
		lexer_parser_executer((*command)->array[y], 0, &_env);
}
