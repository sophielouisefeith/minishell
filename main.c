/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/08 14:49:22 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			main(int argc, char **argv)
{
	int		fd;
	char	*line;
	int		ret;
	int		line_num;
	int 	i;

	line_num = 1;
	ret = 1;
	i = 0;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	while (ret > 0)
	{
		write(1, "$ ", 2);
		ret = get_next_line(fd, &line);
		while (line[i] == ' ')
			i++;
		if (line[i] != '\0')
			parser(line);
		free(line);
		// printf("Return:[%i] - line[%i] = [%s]\n", ret, line_num, line);
		line_num++;
	}
}