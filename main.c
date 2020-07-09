/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/09 15:35:36 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** spaces before commands or returns are allowed.
** return key: prompt on a new line
*/

int			main(int argc, char **argv)
{
	char	*line;
	int		ret;
	int 	i;
	// int		line_num;

	// line_num = 1;
	ret = 1;
	i = 0;
	while (ret > 0)
	{
		write(1, "$ ", 2);
		ret = get_next_line(0, &line);
		if (ret == -1)
			error();
		while (line[i] == ' ')
			i++;
		if (line[i] != '\0')
			parser(line);
		free(line);
		// printf("Return:[%i] - line[%i] = [%s]\n", ret, line_num, line);
		// line_num++;
	}
}