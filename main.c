/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/07 16:04:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/09 12:14:21 by Maran         ########   odam.nl         */
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
	// ./a.out = argc 1 Dus als er meer staat dan ./a.out dan open
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	printf("fd = [%d]\n", fd);
	// if (fd == 0)
	// 	write(1, strerror(errno), ft_strlen(strerror(errno)));
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