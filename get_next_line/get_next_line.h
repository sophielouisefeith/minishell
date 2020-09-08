/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   get_next_line.h                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: msiemons <msiemons@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/01/08 16:37:25 by msiemons      #+#    #+#                 */
/*   Updated: 2020/09/04 16:57:18 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

/*
** Read includes: types, uio, unistd.
** Malloc include: stdlib
*/
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <stdlib.h>

int			get_next_line(int fd, char **line);
size_t		ft_strlen_gnl(const char *s);
char		*ft_strdup_gnl(const char *s1);
char		*ft_strchr_gnl(const char *s, int c);
char		*ft_strjoin_gnl(char *s1, char *s2);
char		*ft_substr_gnl(char *s, unsigned int start, size_t len);

#endif
