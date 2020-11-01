/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_builtin_again.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 17:31:13 by maran         #+#    #+#                 */
/*   Updated: 2020/11/01 12:05:24 by sfeith        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

	// printf("In CBA\n");
	// tester(NULL, *command);
	// if ((*command)->array[y] == NULL && (*command)->array[y + 1] != NULL)		//Scary
	// {
	// 	// printf("in cba y+1 [%s]\n", (*command)->array[y + 1]);
	// 	y++;
	// }

void				check_builtin_again(t_command **command, t_env *_env, int y)
{
	char *new_str;
	char *tmp;
	char *y_space;

	if ((*command)->builtin == builtin_no_com && \
	(*command)->array[y] != NULL && y == 0)
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
			lexer_parser_executer(new_str, &_env);
			g_own_exit = 999;
			free(new_str);
		}
	}
}
