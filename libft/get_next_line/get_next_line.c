/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:37:30 by msiemons      #+#    #+#                 */
/*   Updated: 2020/11/05 17:30:40 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "../libft.h"

static char		*ft_cut(char *new_line, char **line, int *r)
{
	int		i;
	char	*tmp;

	i = 0;
	while (new_line[i] != '\n' && new_line[i] != '\0')
		i++;
	*r = new_line[i] == '\n' ? 1 : 0;
	*line = ft_substr_gnl(new_line, 0, i);
	if (*line == NULL)
		return (NULL);
	tmp = ft_substr_gnl(new_line, i + 1, (ft_strlen(new_line) - i));
	if (tmp == NULL)
		return (NULL);
	free(new_line);
	return (tmp);
}

/*
** Added for signals:
** (ret > 0), (ret == 0 && flag), ft_putstr("  \b\b");
*/

static int		check_return_read(int *flag, int ret, char *new_line, char *buf)
{
	if (ret == -1)
	{
		free(new_line);
		free(buf);
		return (0);
	}
	if (ret > 0)
		*flag = ret;
	if (ret == 0 && *flag)
		ret = *flag;
	ft_putstr("  \b\b");
	return (1);
}

static char		*ft_read(int fd, char *new_line, int ret)
{
	char			*buf;
	int				flag;

	flag = 0;
	while (ret > 0)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (buf == NULL)
		{
			free(new_line);
			return (NULL);
		}
		ret = read(fd, buf, BUFFER_SIZE);
		if (!check_return_read(&flag, ret, new_line, buf))
			return (NULL);
		buf[ret] = '\0';
		new_line = ft_strjoin_gnl(new_line, buf);
		if (new_line == NULL)
			return (NULL);
		if (ft_strchr_gnl(new_line, '\n'))
			break ;
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
	// if (new_line[fd] == NULL)			//
	// 	ret = ft_read_line(fd, new_line, ret); //
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
