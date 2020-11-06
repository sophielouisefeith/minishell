/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   GNL_primoz.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/04 21:59:43 by maran         #+#    #+#                 */
/*   Updated: 2020/11/06 09:57:59 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

static int		ft_read_line(int fd, char **store)
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
		return (-1);
		// return (clean(fd, store));
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


====================================

//PRMERKUU:

// static int		ft_read_line(int fd, char **store)
// {
// 	char 	*tmp;
// 	char 	buf[BUFFER_SIZE + 1];
// 	int		res;

// 	res = read(fd, buf, BUFFER_SIZE);
// 	if (res < 0)
// 		return (-1);
// 	buf[res] = '\0';
// 	if (!store[fd])
// 		store[fd] = ft_strdup(buf);
// 	else
// 	{
// 		tmp = store[fd];
// 		store[fd] = ft_strjoin(tmp, buf);
// 		free(tmp);
// 		tmp = NULL;
// 	}
// 	if (!store[fd])
// 		return (-1);
// 		// return (clean(fd, store));
// 	return (res);
// }

// static int	g_res = 1;

// int			get_next_line(int fd, char **line)
// {
// 	// char 		*tmp;
// 	char 		*ptr;
// 	static char *store[1];

// 	if (BUFFER_SIZE <= 0 || !line || read(fd, NULL, 0) == -1)
// 		return (-1);
// 	if (store[fd] == NULL)
// 		g_res = ft_read_line(fd, store);
// 	while (!ft_strchr(store[fd], '\n'))
// 		g_res = ft_read_line(fd, store);
// 	if (g_res < 0)
// 		return (-1);
// 	ptr = ft_strchr(store[fd], '\n');
// 	// if (ptr != NULL)
// 	// {
// 	// 	*ptr = '\0';				//ipv \n maak er een \0 van
// 	// 	*line = ft_strdup(store[fd]);
// 	// 	tmp = store[fd];
// 	// 	store[fd] = ft_strdup(ptr + 1);
// 	// 	free(tmp);
// 	// 	tmp = NULL;
// 	// 	return(1);
// 	// 	// return (clean(fd, &store[fd]));
// 	// }
// 	*line = ft_strdup(store[fd]);
// 	// free stuff
// 	return ((!(*line)) ? -1 : 0);
// }

=========Late night Probeersel===========================

// static int		check_return_read(int *flag, int ret, char *new_line, char *buf)
// {
// 	(void)buf;
// 	(void)new_line;
// 	// if (ret == -1)
// 	// {
// 	// 	free(new_line);
// 	// 	return (0);
// 	// }
// 	if (ret > 0)				//Bytes gelezen dan flag is TRUE
// 		*flag = ret;		
// 	if (ret == 0 && *flag)		//Reading EOF && Er zijn bytes gelezen voorheen dan zet ret op > 0
// 	{
// 		// printf("EOF en voorheen BYTES\n");
// 		ret = *flag;
// 	}
// 	ft_putstr("  \b\b");
// 	return (ret);
// }

static char		*ft_read(int fd, char *new_line, int ret)
{
	char 	buf[BUFFER_SIZE + 1];

	if(!read(fd, NULL, BUFFER_SIZE))				//als direct ctrl d
	{
		write(1, "exit\n", 5);
		exit(0);
	}
	while (!ft_strchr_gnl(new_line, '\n'))
	{
		ret = read(fd, buf, BUFFER_SIZE);			//ctrl D -> ret ==0
		// ft_putstr("  \b\b");
		buf[ret] = '\0';
		new_line = ft_strjoin_gnl(new_line, buf);
		if (new_line == NULL)
			return (NULL);
	}
	return (new_line);
}

int				get_next_line(int fd, char **line)
{
	int				ret;
	static char		*new_line;
	int				r;

	if (fd < 0 || !line || BUFFER_SIZE <= 0)
		return (-1);
	ret = 1;
	r = 1;
	if (new_line == NULL)
		new_line = ft_strdup("");
	if (new_line == NULL)
		return (-1);
	new_line = ft_read(fd, new_line, ret);
	if (new_line == NULL)
		return (-1);
	new_line = ft_cut(new_line, line, &r);
	if (new_line == NULL)
		return (-1);
	if (r == 0)
	{
		free(new_line);
		new_line = 0;
	}
	return (r);
}