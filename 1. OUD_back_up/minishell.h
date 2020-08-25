/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 18:26:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/15 23:36:21 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <errno.h>
#include <string.h>

/*
** Checken of later verwijderen:
*/
#include <stdio.h>
// #include <fcntl.h>
// #include <stdlib.h>


typedef struct				s_parse {
	char 					*str;
	int						type;
	struct		s_parse 	*next;
}							t_parse;

int							ft_strcmp(const char *s1, const char *s2);
void						error(void);
void						parser(char *line);
int							echo(t_parse **head);

t_parse						*ll_new_node(void *content);
void						ll_split(t_parse **head, char const *s, char c);
void						ll_lstadd_back(t_parse **head, t_parse *new);
void						ll_lstclear(t_parse **lst);

// int	                		lexer(char *str);

/*
** redirections and pipe pas later naar kijken
*/
// int        					check_redirection(t_parse *list, char **file_name);
// void         				redirection(t_parse *list, int flag_redirection, int flag_n, char *file_name);

#endif
