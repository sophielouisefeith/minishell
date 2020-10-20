/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:37:30 by msiemons      #+#    #+#                 */
/*   Updated: 2020/10/20 12:45:57 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t			ft_strlen_gnl(const char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

/// NEW VOOR CTRLD
static int		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}
static void		ft_putstr(char *str)
{
	int len;

	len = ft_strlen(str);
	write(1, str, len);
	return ;
}
///

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
	tmp = ft_substr_gnl(new_line, i + 1, (ft_strlen_gnl(new_line) - i));
	if (tmp == NULL)
		return (NULL);
	free(new_line);
	return (tmp);
}

static char		*ft_read(int fd, char *new_line, int ret)
{
	char			*buf;
	int 			flag;

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
		if (ret == -1)
		{
			free(new_line);
			free(buf);
			return (NULL);
		}
		if (ret > 0)						//new
			flag = ret;						//
		if (ret == 0 && flag)				//
			ret = flag;						//
		ft_putstr("  \b\b");				//new
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
		new_line = ft_strdup_gnl("");
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
