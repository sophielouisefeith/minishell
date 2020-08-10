/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 18:26:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/08/10 16:33:44 by maran         ########   odam.nl         */
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
#include <fcntl.h>
#include <stdlib.h>
//#define errno (*error_free())

enum	token_type{
	token_null = 0,
	token_general,
	token_whitespace,
	token_quote,
	token_dquote, 
	token_pipe,
	token_semicolon,
	token_redirection, 						//new
	token_redirection_greater,
	token_redirection_lesser,
	token_redirection_dgreater,
	token_dollar,
};

enum	builtin_type{
	builtin_no,
	builtin_echo,
	builtin_cd,
	builtin_pwd,
	builtin_export,
	builtin_unset,
	builtin_env,
	builtin_exit
};

enum	error_type{
	erro_general,
	error_malloc,					//	strerror(errno);
	erroc_notavalidfile,			//	strerror(errno);
	error_Multipleline,
	error_notavalidentifier,		//	strerror(errno);
	//error_fork,
	//error_openingpipe,
	
};

typedef struct				s_lexer{
	char 					*str;
	int						*token;
	struct		s_lexer 	*next;
}							t_lexer;




typedef struct				s_output{
	char					*str_output;
	int						token_output;

	struct		s_output 	*next_output;
}							t_output;




typedef struct				s_input{
	char					*str_input;
	int						token_input;

	struct		s_input 	*next_input;
}							t_input;

// typedef struct			s_output_modus{
// 	//char					*str;
// 	char 					**array_modus;
// 	struct		s_lexer 	*next;
// }							t_output_modus;

typedef struct				s_command {
	char					**array;
	int						builtin;
	
	struct s_output			*output;    
	struct s_input			*input;     
	// struct s_list 			output_modus; // trunk append
	int						pipe_before;
	int						pipe_after;
	int						sem;
	struct		s_command 	*next;
}							t_command;

typedef struct				s_env{
	char 					*name;
	char					*value;
	struct		s_env   	*next;
}							t_env;

void							lexer(t_lexer **head, char *line);
int								*allocate_memory_int_string(int i);

int								ft_strcmp(const char *s1, const char *s2);
char 							*str_from_char(char c);
char 							*str_redirection_dgreater(void);

int								is_single_quote(char c);
int								is_double_quote(char c);
int								is_whitespace(char c);
int								is_operator(char c);
int								is_metachar(char c);

t_lexer							*ll_new_node(char *str, int *token);
void							ll_lstadd_back(t_lexer **head, t_lexer *new);

int								this_is_a_test(int c);

/*transform */
int								parser(t_lexer **sort, t_command **command, int count);
int         					get_builtin_type(char *str);
// char            				*trunc_quotes(t_lexer *list,char *str);
char            				*trunc_quotes(char *str);
int								check_builtin_node(t_lexer **head);
int    							check_token(char *str);
int								get_token_type(char *line, int *i);
int								count_node(t_lexer *sort);
int								fill_operator(t_lexer *head, int count);
void	        				redirection(t_lexer **head, t_command **tmp);


/*output */
void            				output_fill(t_lexer **head, t_command **tmp);


/* input */
void            				input_fill(t_lexer **head, t_command **tmp);


/*execute*/
int             				execute(void);
int								execute_cd(void);
int          					execute_pwd(void);
t_env                 			*save_env();
void			    			ll_lstadd_back_env(t_env **head, t_env *new);
t_env			    			*ll_new_node_env(char *name, char *value);
void        					execute_env(t_env *env);
int	            				execute_export(t_env **env);
void        					execute_unset(t_env **env);
void        					execute_exit(void);
int								execute_echo(t_command *head_command);

/*test */
void     						tester_pars(t_lexer *lexer, t_command *command);

/*free */				
int            					free_array(char **array);
void      						free_str(char *str);
void            				free_complete(int mistake);

/*error */						
char                			*strerror_i(int errnum);
int								error_free(int mistake);
#endif
