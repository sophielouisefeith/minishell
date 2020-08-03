/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/03 17:10:47 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Spaces before commands or returns are allowed.
** Return key: prompt on a new line
*/

int				main(int argc, char **argv)
{
	char	*line;
	int		ret;
	int 	i;
	
	ret = 1;
	while (ret > 0)
	{
		i = 0;
		write(1, "$ ", 2);
		ret = get_next_line(0, &line);
		// if (ret == -1)
		// 	error();
		if (line[i] != '\0')
			lexer(line);
		//tester(line);
		// execute();
		free(line);
		line = NULL;
	}
}
