/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 16:18:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/06 17:26:20 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line/get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/errno.h>

#include "libft/libft.h"
#include <stdio.h>
extern int errno;

typedef struct s_parseinfo {
	

}				t_parseinfo;

void		parse(char *line)
{
	int i;
	int y;
	char **array;
	
	i = 0;
	y = 0;
	printf("----In parse----\n");
	// while (line[i] == ' ' || line[i] == '\t')
	// 	i++;
	array = ft_split(line, ' ');
	while (array[y])
	{
		printf("printf [%s]\n", array[y]);
		y++;
	}
	printf("----End parse----\n");
	
}

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