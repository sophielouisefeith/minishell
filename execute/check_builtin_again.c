/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   check_builtin_again.c                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/07 17:31:13 by maran         #+#    #+#                 */
/*   Updated: 2020/10/07 19:18:43 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*
** Scary;  gaat  dit in alle volgordes goed ? Ook eng met leaks. IF LEAKS KIJK ZEKER HIER!!
*/

void			lexer_parser_executer(char *line, int i, t_env **_env);

void				check_builtin_again(t_command **command, t_env *_env, int y)
{
	// printf("(*command)->builtin = %d\n", (*command)->builtin);
	if ((*command)->builtin == builtin_no_com)
		lexer_parser_executer((*command)->array[y], 0, &_env);
	// printf("UIT\n");
}

// Werkt niet:
// export POEP="ls -la"
//echo hoi | $POEP

// export POEP="grep main"
// ls > x1 ; cat x1 | $POEP

//hallo $POEP --> bash: hallo: command not found  --> dan er al uit klappen! Behalve als $