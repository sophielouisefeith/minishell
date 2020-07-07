/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parser.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 16:18:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/07 14:02:18 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern int errno;

static void		parse(char *line)
{
	int i;
	int y;
	// char **array;
	t_parse	*head;
	
	
	i = 0;
	y = 0;
	printf("----In parse----\n");
	head = ll_split(line, ' ');
	printf("[%s] [%s] [%s]- ", head->str, head->next->str, head->next->next->str);
	
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