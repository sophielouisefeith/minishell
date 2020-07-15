/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 13:00:26 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/07/08 15:53:58 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include  "minishell.h"

void			error(char *str, int i)
{

	write(1, "Bash command not found:\n", 22);
	write(1, str, i);
	write(1, ".\n", 2);
	exit(0);
}