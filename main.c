/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/07 16:05:02 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;
	int		i;

	i = 1;
	ret = 1;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	while (ret > 0)
	{
		write(1, "% ", 2);
		ret = get_next_line(fd, &line);
		printf("Return:[%i] - line[%i] = [%s]\n", ret, i, line);
		parse(line);
		i++;
		free(line);
	}
}