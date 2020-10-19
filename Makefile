# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sfeith <sfeith@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/24 16:17:15 by sfeith        #+#    #+#                  #
#    Updated: 2020/10/19 18:18:44 by maran         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = minishell.a

LIBFT = libft

SRC =  main.c lexer.c lexer_utils.c character_check.c ft_strcmp.c\
		save_env.c\
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\
		ll_make_list_lexer.c parser.c parser_utils.c\
		ll_make_list_parser.c\
		free_list.c \
		tester.c\
		output.c input.c\
		execute/execute.c\
		execute/check_specials.c\
		execute/check_specials_utils.c\
		execute/execute_builtin.c\
		execute/echo.c\
		execute/execute_cd.c  execute/execute_pwd.c\
		execute/env_ll_to_array.c\
		execute/env.c\
		execute/execute_unset.c\
		execute/execute_exit.c\
		execute/parameter_expansion.c\
		execute/parameter_expansion_utils.c\
		execute/execute_export.c\
		execute/ft_split2.c\
		get_path.c\
		error.c\
		execute/check_builtin_again.c\
		
		# free.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)
	
$(NAME): $(OBJ) lib_ft
	@ar rcs $(LIB) $(OBJ)
	@$(CC) $(CFLAGS) $(LIB)
	@echo "\n>>>>>Finished making<<<<<"

lib_ft:
	@echo "\n>>>>>Making lib_ft<<<<<"
	@make -C $(LIBFT)
	@make bonus -C $(LIBFT)
	@cp libft/libft.a ./$(LIB)

%.o: %.c
	@echo $@
	@$(CC) $(CFLAGS) -c $< -o $@ -D BUFFER_SIZE=128

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	@$(RM) $(LIB) a.out
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re