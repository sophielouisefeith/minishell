/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   minishell.h                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: maran <maran@student.42.fr>                  +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/07/06 18:26:32 by Maran         #+#    #+#                 */
/*   Updated: 2020/11/06 17:39:47 by maran         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include "../libft/libft.h"
# include <errno.h>
# include <string.h>
# include <signal.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>

int		g_exit_status;
int		g_own_exit;

enum	e_token_type{
	token_null,
	token_general,
	token_whitespace,
	token_quote,
	token_dquote,
	token_pipe,
	token_semicolon,
	token_redirection,
	token_redirection_greater,
	token_redirection_lesser,
	token_redirection_dgreater,
	token_dollar,
}		t_token_type;

enum	e_builtin_type{
	builtin_no_com,
	builtin_no,
	builtin_echo,
	builtin_cd,
	builtin_pwd,
	builtin_export,
	builtin_unset,
	builtin_env,
	builtin_exit,
	executable
}		t_builtin_type;

typedef struct				s_lexer{
	char					*str;
	int						*token;
	struct s_lexer			*next_sort;
}							t_lexer;

typedef struct				s_output{
	char					*str_output;
	int						token;
	struct s_output			*next_output;
}							t_output;

typedef struct				s_input{
	char					*str_input;
	struct s_input			*next_input;
}							t_input;

typedef struct				s_command {
	char					**array;
	int						builtin;
	struct s_output			*output;
	struct s_input			*input;
	int						pipe_before;
	int						pipe_after;
	int						sem;
	struct s_command		*next_command;
}							t_command;

typedef struct				s_env{
	char					*name;
	char					*value;
	int						equal;
	struct s_env			*next;
}							t_env;

typedef struct				s_dollar{
	char					*new_str1;
	char					*parameter;
	char					*new_str2;
	int						ret;

	int						flag_qm;
	int						flag_group2;
	int						quote;
}							t_dollar;

typedef struct				s_execute{
	int						tmpin;
	int						tmpout;
	int						fdin;
	int						fdout;
	int						i;
	int						len_list;
	int						fdpipe[2];
}							t_execute;

void						lexer_parser_executer(char *line, t_env **envb);
t_env						*save_env(char **env);
t_env						*ll_new_node_env(char *name,
							char *value, int equal);
void						ll_lstadd_back_env(t_env **env, t_env *new);
void						sighandler(int signum);
void						sighandler_execve(int status);
void						ctrl_d(void);
void						signal_reset(int sig_num);
void						lexer(t_lexer **head, char *line);
int							check_redirections(char *line, int i, int type);
int							get_token_type(char *line, int *i);
int							*allocate_memory_int_string(int i);
char						*str_from_char(char c);
char						*str_redirection_dgreater(void);
int							is_whitespace(char c);
int							is_single_quote(char c);
int							is_double_quote(char c);
int							is_backslash(char c);
int							is_operator(char c);
int							is_metachar(char c);
t_lexer						*ll_new_node_lexer(char *str, int *token);
void						ll_lstadd_back_lexer(t_lexer **head, t_lexer *new);
int							parser(t_lexer **sort,
							t_command **command, int pipe_status);
int							count_node(t_lexer **sort, int builtin);
int							get_builtin_type(char *str);
int							check_builtin_node(t_lexer **sort);
void						ll_lstadd_back_command(t_command **command,
							t_command *new);
t_command					*ll_new_node_command(int num_nodes, int builtin);
void						input_fill(t_lexer **sort, t_command **tmp);
void						output_fill(t_lexer **sort,
							t_command **tmp, int token);
int							echo(char **array);
char						*strdup_and_free(char **str);
void						free_env(t_env *envb);
void						free_array(char **array);
void						free_list_lexer(t_lexer **sort);
void						free_list_parser(t_command **command);
void						*execute(t_command **command, t_env **envb);
void						builtin_another_program(t_command **command,
							t_env **envb);
int							execute_cd(t_command *command, t_env **envb);
int							execute_pwd(t_command *command);
int							execute_export(t_env **envb,
							t_command **command);
int							execute_unset(t_command *command, t_env **envb);
int							execute_exit(t_command *command);
void						execute_builtin(t_command **command,
							t_env **envb);
char						**ft_split2(char const *s, char c);
int							env(t_env *envb);
char						**env_ll_to_array(t_env *env);
int							fill_fdout(t_output *output, int tmpout);
void						execute_output(t_command **command,
							t_execute **exe, t_env **envb);
void						*clean_exit_execute(t_execute **exe);
void						initialise_execute(t_command *command,
							t_execute **exe);
int							execute_fail(t_command *command, char **array);
void						swap(char **s1, char **s2);
void						swap_int(int *s1, int *s2);
void						alpha_env_list(t_env *alpha_env);
void						free_if_dollar(t_dollar **dollar);
void						check_builtin_again(t_command **command,
							t_env *envb, int y);
void						error_pwd_unset(char *str, char *path);
int							check_for_other_parameters(char **array, int y);
void						initiate_dollar(t_dollar *dollar, int quote);
int							dollar_is_special_char(char *str, int i);
void						parameter_expansion(t_command **command,
							t_env *envb);
char						*if_dollar(char *str, int *i,
							t_env *envb, int quote);
char						*search_node(t_env *envb, char *search);
int							is_special_char(char *str, int i);
char						*join_strings(char *new_str1, char *parameter,
							char *new_str2);
void						parameter_not_exist(t_command
							**command, int *y);
void						complete_path(t_command **command, t_env *envb);
void						check_specials(t_command **command,
							t_env *envb);
char						*delete_double_quotes(char *src,
							int start, int end);
char						*delete_escape_char(char **src, int n);
char						*delete_quotes(char *src, char garbage);
char						*check_backslash_and_dollar(char **str,
							int *i, t_env *envb);
char						*tmp_tolower(char *str);
char						*error_command(char *str, int i,
							t_command *command);
int							error(t_command *command);
char						*error_path(int i, char *str);
char						*error_qoute(char *str);
void						set_exit_status(void);
int							malloc_fail(void);
char						*translate_builtin(int b, char *str);
int							error_redirections(char c, int error_num,
							int i, char *line);
int							errno_error(char *str, t_command *command);
void						set_exit_status(void);
char						*not_part(char *str);
int							error_redi_one(char c, int i, char *line);

#endif
