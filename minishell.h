/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: sfeith <sfeith@student.codam.nl>             +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/02 14:37:03 by sfeith        #+#    #+#                 */
/*   Updated: 2020/07/15 14:01:40 by SophieLouis   ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */




#ifndef minishell_H
# define minishell_H

#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 6
# endif


typedef struct      s_list
{
   char                *data;

    struct s_list      *next;
           
}                   t_list;




typedef struct		s_mini
{

	char			*line;
    char            **array;
	
}					t_mini;

void            parser(char *line);
t_list			*split(char const *s, char c);
void			error(char *str, int i);
t_list	        *ft_lstnew(char *str1);

int		        get_next_line(const int fd, char **line);
size_t	        ft_strlen(const char *s);
char	        *ft_strdup(const char *s1);
char	        *ft_strjoin(char *s1, char *s2);
char	        *ft_strchr(const char *s, int c);
char	        *ft_substr(char *s, unsigned int start, size_t len);
size_t	        ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	        *ft_strchr(const char *s, int c);
void	        ft_lstadd_back(t_list **alst, t_list *new);

# endif