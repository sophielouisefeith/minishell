/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   GNL_primoz.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 21:59:43 by maran         #+#    #+#                 */
/*   Updated: 2020/11/05 11:16:40 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

static int		ft_read(int fd, char **store)
{
	char 	*tmp;
	char 	buf[BUFFER_SIZE + 1];
	int		res;

	res = read(fd, buf, BUFFER_SIZE);
	if (res < 0)
		return (-1);
	buf[res] = '\0';
	if (!store[fd])
		store[fd] = ft_strdup(buf);
	else
	{
		tmp = store[fd];
		store[fd] = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		// ft_free(tmp);
	}
	if (!store[fd])
		return (clean(fd, store));
	return (res);
}

static int	g_res = 1;

int			get_next_line(int fd, char **line)
{
	char 		*tmp;
	char 		*ptr;
	static char *store[1];

	if (BUFFER_SIZE <= 0 || !line || read(fd, NULL, 0) == -1)
		return (-1);
	if (store[fd] == NULL)
		g_res = ft_read_line(fd, store);
	while (ft_strchr(store[fd], '\n') && g_res > 0)
		g_res = ft_read_line(fd, store);
	if (g_res < 0)
		return (-1);
	ptr = ft_strchr(store[fd], '\n');
	if (ptr != NULL)
	{
		*ptr = '\0';
		*line = ft_strdup(store[fd]);
		tmp = store[fd];
		store[fd] = ft_strdup(ptr + 1);
		// ft_free(tmp);
		free(tmp);
		tmp = NULL;
		return (clean(fd, &store[fd]));
	}
}
