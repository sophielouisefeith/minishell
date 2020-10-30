/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: Maran <Maran@student.codam.nl>               +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 18:26:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/10/30 17:44:36 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include "../libft/libft.h"

#include <errno.h>
#include <string.h>
#include <signal.h>
#include <sys/stat.h>
#include <unistd.h>

/*
** Checken of later verwijderen:
*/
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
//#define errno (*error_free())

int		g_exit_status;
int		g_own_exit;

enum	token_type{
	token_null,
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

/*
** TO DO: beschrijven wanneer no_com en no
*/

enum	builtin_type{
	builtin_no_com,
	builtin_no,
	builtin_echo,
	builtin_cd,
	builtin_pwd,
	builtin_export,
	builtin_unset,
	builtin_env,
	builtin_exit,
	executable								//new (na vakantie)
};


typedef struct				s_lexer{
	char 					*str;
	int						*token;
	struct		s_lexer 	*next_sort;
}							t_lexer;


typedef struct				s_output{
	char					*str_output;
	int						token;
	struct		s_output 	*next_output;
}							t_output;


typedef struct				s_input{
	char					*str_input;
	struct		s_input 	*next_input;
}							t_input;

typedef struct				s_command {
	
	char					**array;
	// int						*quote;						//new //GEBRUIKEN WE DEZE NOG?
	int						builtin;
	struct s_output			*output;    
	struct s_input			*input;    
	int						pipe_before;
	int						pipe_after;
	int						sem;
	struct		s_command 	*next_command;
}							t_command;

typedef struct				s_env{
	char 					*name;
	char					*value;
	int						equal;
	struct		s_env   	*next;
}							t_env;

typedef struct				s_dollar{
	char 					*new_str1;
	char					*parameter;
	char 					*new_str2;
	int						ret;

	int						flag_qm;			//questionmark
	int 					flag_group2;
	int						quote;
}							t_dollar;

typedef struct				s_execute{
	int     				tmpin;
    int    					tmpout;
    int     				fdin;
    int     				fdout;
	int    					i;
    int     				len_list;
    int     				fdpipe[2];
}							t_execute;


/*******Cleaning*********/
/* main*/
void						lexer_parser_executer(char *line, t_env **_env);

/* Save_env*/
t_env                 		*save_env(char **env);
t_env						*ll_new_node_env(char *name, char *value, int equal);
void						ll_lstadd_back_env(t_env **env, t_env *new);

/* Signals*/
void 						sighandler(int signum);
void						sighandler_execve(int status);
void						ctrl_d(void);
void						signal_reset(int sig_num);

/* Lexer*/
void						lexer(t_lexer **head, char *line);

/* Lexer_utils*/
int							check_redirections(char *line, int i, int type);
int							get_token_type(char *line, int *i);
int							*allocate_memory_int_string(int i);
char 						*str_from_char(char c);
char 						*str_redirection_dgreater(void);

/* Character_check*/
int								is_whitespace(char c);
int								is_single_quote(char c);
int								is_double_quote(char c);
int								is_backslash(char c);

/* Character_check2*/
int								is_operator(char c);
int								is_metachar(char c);

/* ll_make_list_lexer*/
t_lexer							*ll_new_node_lexer(char *str, int *token);
void							ll_lstadd_back_lexer(t_lexer **head, t_lexer *new);


/*******End Cleaning*******/

/*******Remove*********/
void            				tester(t_lexer *sort, t_command *command);
/*******End remove*******/








int								ft_strcmp(const char *s1, const char *s2);

/*parsing */
int								parser(t_lexer **sort, t_command **command, int count, t_env **_env);
// int								count_node(t_lexer *sort);
int								count_node(t_lexer *sort, int builtin);
// int								count_node(t_lexer **sort, int builtin);
char            				*trunc_quotes(char *str);
int         					get_builtin_type(char *str);
int								check_builtin_node(t_lexer **head, t_env **_env);


/*Check path */
char							*check_path(t_env *env, char *str);




t_command	    				*ll_new_node_command();
void		    				ll_lstadd_back_command(t_command **command, t_command *new);


/*output */
void            				output_fill(t_lexer **sort, t_command **tmp, int token);

/* input */
void            				input_fill(t_lexer **head, t_command **tmp);



/*test */
void     						tester_pars(t_lexer *lexer, t_command *command);

/*free */				
void           					free_array(char **array);
void        					free_list(t_lexer **sort, t_command **command);
void        					free_list_lexer(t_lexer **sort);
void							free_list_parser(t_command **command);
void         					free_env(t_env *_env);

// void      						free_str(char *str);
// void            				free_complete(int mistake);
// void        				    free_list_command(t_command **command);

/*error */						
// char                			*strerror_i(int errnum);
// int								error_free(int mistake);
char							*error_command(char *str, int i, t_command *command);
int								error(t_command *command);
char 							*error_qoute(char *str);
void							set_exit_status(void);
int								malloc_fail(void);
/*execute*/
void            				*execute(t_command **command, t_env **env);
void             				execute_builtin(t_command **command, t_env **_env);
void            				execute_command(t_command **command, t_env **_env);
int								lstsize(t_command *command);
void							initialise_execute(t_command *command, t_execute **exe);
void							close_execute(t_execute **exe);
void							execute_output(t_command **command, t_execute **exe,t_env **_env);
int								fill_fdout(t_output *output, int tmpout);
void							builtin_another_program(t_command **command, t_env **_env);

int								echo(char **array);
// void							env(char **array);
int								env(t_env *_env);
char							**env_ll_to_array(t_env *env);

int             				execute_cd(t_command *command, t_env **_env);
int                 			execute_pwd(void);

int            					execute_export(t_env **_env, t_command **command);
char							**ft_split2(char const *s, char c);

int    	    					execute_unset(t_command *command, t_env **_env);
int      						execute_exit(t_command *command);

/* parameter expansion */
void							parameter_expansion(t_command **command, t_env *_env);
// char							*expand(char *str, int i, t_env *_env);
char							*if_dollar(char *str, int *i, t_env *_env, int quote);

char							*search_node(t_env *_env, char *search);
int								is_special_char(char *str, int i);
char							*join_strings(char *new_str1, char *parameter, char *new_str2);


/*new*/
char							*tmp_tolower(char *str);
void								check_specials(t_command **command, t_env *_env);
char							*check_backslash_and_dollar(char *str, int *i, t_env *_env);
char							*delete_double_quotes(char *src, int start, int end);
char							*delete_escape_char(char *src, int n);




char							*delete_quotes(char *src, char garbage);
void							parameter_not_exist(t_command **command, int *y);
char							*delete_escape_char(char *src, int n);


void							check_builtin_again(t_command **command, t_env *_env, int y);


/* >>>>>>>>>>> */
int								error_redirections(char c, int error_num, int i, char *line);
// char							*error_no_path(char *str);
// void							*no_file(char *str);
int								errno_error(char *str);
void							set_exit_status(void);

char							*not_part(char *str);
char 							*translate_builtin(int b, char *str);

int				dollar_is_special_char(char *str, int i);
void			initiate_dollar(t_dollar *dollar, int quote);


char		*make_tmp(char **str);

/// new error for final version

char				*error_path(int i, char *str);


// ./ <h hebben een andere exit code, <<<<< doet het ineens nu ook niet meer daar naar kijken 
//kijken met de fd[3] waar dat dan allemaal aangepast moet worden. 
#endif
