/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_get_next_line.c                               :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:43:11 by msiemons      #+#    #+#                 */
/*   Updated: 2020/07/06 16:36:49 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/errno.h>
extern int errno;

/*
** TEST on: Invalid file "24", error returns, buffersize >1024, <8, 1, 
** 9999, 10000000
** exactly like line to read (+1 & -1), Read on stdin & file,
** multiple/single long line > 2k, short line < 4 && 1
** Empty last line(s)
** Read from a file, from a redirection, from standard input (CTRL-D)
*/

int				main(int argc, char **argv)
{
	// int		fd1;
	int		fd3;
	char	*line;
	int		ret;
	int		i;

	if (argc > 1)
		fd3 = open(argv[1], O_RDONLY);
	// fd1 = open("text_files/leeg.txt", O_RDONLY);
	// if (fd1 == -1)
	// {
	// 	printf("Error Number [%d]\n", errno);
	// 	perror("Program");
	// }
	i = 1;
	ret = 1;
	while (ret > 0)
	{
		ret = get_next_line(fd3, &line);
		printf("Return:[%i] - line[%i] = [%s]\n", ret, i, line);
		i++;
		free(line);
	}
/* BONUS
	// int ret_end = 1;
	// int cur_fd;

	// while (ret == 1 || ret_end == 1)
    // {
    //     ret = ret_end;
    //     cur_fd = (i % 2 == 1) ? fd1 : fd2;
    //     ret_end = get_next_line(cur_fd, &line);
    //     printf("FD[%d]: [%i] [%s]\n", cur_fd, ret_end, line);
    //     i++;
    //     free(line);
    // }
 */
	// while (1){}
	return (0);
}
