/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 18:26:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/09 11:40:12 by Maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "get_next_line/get_next_line.h"
#include "libft/libft.h"
#include <errno.h>
#include <string.h>

#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>

typedef struct			s_parse {
	char 				*str;
	struct		s_parse *next;
}						t_parse;

void				parser(char *line);
void				ll_split(t_parse **head, char const *s, char c);
// void				ll_list_push_front(t_parse **begin_list, void *data);
t_parse				*ll_new_node(void *content);
void				ll_lstadd_back(t_parse **alst, t_parse *new);


void				ll_add_back(t_parse **begin_list, void *data);
int					ft_strcmp(const char *s1, const char *s2);

#endif