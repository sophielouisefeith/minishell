/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 18:26:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/07/23 16:35:22 by sfeith        ########   odam.nl         */
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

enum	token_type{
	token_null = 0,
	token_general,
	token_whitespace,
	token_quote,
	token_dquote, 
	token_pipe,
	token_semicolon,
	token_redirection_greater,
	token_redirection_lesser,
	token_redirection_dgreater,
	token_dollar,
};

// enum	builtin{
// 	builtin_echo,
// 	builtin_cd,
// 	builtin_pwd,
// 	builtin_export,
// 	builtin_unset,
// 	builtin_env,
// 	builtin_exit
// };

typedef struct				s_lexer{
	char 					*str;
	int						*token;
	struct		s_lexer 	*next;
}							t_lexer;

// typedef struct				s_parser {
// 	char 					*str;
// 	int						*token;
// 	struct		s_lexer 	*next;
// }							t_parser;

typedef struct				s_command {
	struct s_list			output;    // dit is dus een link list voor alle outputs // moeten we hier dan * van maken 
	struct s_list			input;     // dit is dus een link list voor de input
	struct s_list 			output_modus; // trunk append
	int						pipe_before;
	int						pipe_after;

}							t_command;


void						lexer(char *line);

int							ft_strcmp(const char *s1, const char *s2);
char 						*str_from_char(char c);
char 						*str_redirection_dgreater(void);

int							is_single_quote(char c);
int							is_double_quote(char c);
int							is_whitespace(char c);
int							is_operator(char c);
int							is_metachar(char c);

t_lexer						*ll_new_node(void *content, int *token);
void						ll_lstadd_back(t_lexer **head, t_lexer *new);

int							this_is_a_test(int c);

/*transform */
void							transform(t_lexer *list);

#endif
