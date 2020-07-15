/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utilitise.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/08 13:04:57 by SophieLouis   #+#    #+#                 */
/*   Updated: 2020/07/15 13:54:00 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include  "minishell.h"

size_t				ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char			*ft_cut(char *new, char **line, int *r)
{
	int		i;
	char	*temp;

	i = 0;
	while (new[i] != '\0' && new[i] != '\n')
		i++;
	*line = ft_substr(new, 0, i);
	if (*line == NULL)
	{
		free(new);
		return (NULL);
	}
	if (new[i] == '\0')
		*r = 0;
	temp = ft_substr(new, i + 1, ft_strlen(new) - i);
	free(new);
	return (temp);
}

static char			*ft_treatment(char *new, int ret, int fd)
{
	char	*buf;

	while (ret > 0)
	{
		buf = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
		if (buf == 0)
		{
			free(new);
			return (NULL);
		}
		ret = (read(fd, buf, BUFFER_SIZE));
		if (ret == -1)
		{
			free(buf);
			free(new);
			return (NULL);
		}
		buf[ret] = '\0';
		new = ft_strjoin(new, buf);
		if (new == NULL)
			return (NULL);
		if (ft_strchr(new, '\n'))
			break ;
	}
	return (new);
}

int					get_next_line(const int fd, char **line)
{
	int			ret;
	static char *new;
	int			r;

	ret = 1;
	r = 1;
	if (fd < 0 || !line || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (-1);
	if (new == NULL)
		new = ft_strdup("");
	if (new == NULL)
		return (-1);
	new = ft_treatment(new, ret, fd);
	if (new == NULL)
		return (-1);
	new = ft_cut(new, line, &r);
	if (new == NULL)
		return (-1);
	if (r == 0)
	{
		free(new);
		new = 0;
	}
	return (r);
}

char			*ft_strdup(const char *s1)
{
	int		len;
	char	*str;

	len = 0;
	str = (char *)malloc(sizeof(char) * (ft_strlen(s1) + 1));
	if (str == 0)
		return (0);
	while (s1[len])
	{
		str[len] = s1[len];
		len++;
	}
	str[len] = '\0';
	return (str);
}

static char		*ft_strcpy(char *dest, char const *src1, char const *src2)
{
	int i;
	int c;

	i = 0;
	c = 0;
	while (src1[i] != '\0')
	{
		dest[i] = src1[i];
		i++;
	}
	while (src2[c] != '\0')
	{
		dest[i] = src2[c];
		i++;
		c++;
	}
	dest[i] = '\0';
	return (dest);
}

char			*ft_strjoin(char *s1, char *s2)
{
	size_t		s1len;
	size_t		s2len;
	char		*ns;

	if (!s2)
		return (NULL);
	s1len = ft_strlen(s1);
	s2len = ft_strlen(s2);
	ns = (char *)malloc((s1len + s2len + 1) * sizeof(char));
	if (ns == NULL)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_strcpy(ns, s1, s2);
	free(s1);
	free(s2);
	return (ns);
}

char			*ft_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
			return ((char*)s);
		s++;
	}
	if (*s == c)
		return ((char*)s);
	return (0);
}

char			*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	srclen;
	char	*sub;

	i = 0;
	if (!s)
		return (NULL);
	srclen = ft_strlen(s);
	sub = (char *)malloc(sizeof(char) * len + 1);
	if (sub == NULL)
	{
		free(s);
		return (NULL);
	}
	while (i < len && start < srclen)
	{
		sub[i] = s[start];
		i++;
		start++;
	}
	sub[i] = '\0';
	return (sub);
}
