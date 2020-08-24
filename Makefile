# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Maran <Maran@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/06 17:19:34 by Maran         #+#    #+#                  #
<<<<<<< HEAD
#    Updated: 2020/08/24 14:14:54 by sfeith        ########   odam.nl          #
=======
#    Updated: 2020/08/24 12:16:37 by maran         ########   odam.nl          #
>>>>>>> 774e9d10d21ff0621f860d1ea3b42a0fab8ea63f
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = minishell.a

LIBFT = libft

SRC =  main.c lexer.c lexer_utils.c character_check.c ft_strcmp.c\
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\
		ll_make_list_lexer.c parser.c parser_utils.c\
		ll_make_list_parser.c\
		free_list.c \
		tester.c\
		output.c input.c\
		sophie_execute/execute_sophie.c\
		sophie_execute/execute_builtin.c\
		sophie_execute/execute_sophie.c\
		sophie_execute/echo.c \
		builtins/execute_cd.c  builtins/execute_pwd.c\
		#builtins/execute.c builtins/execute_echo.c builtins/execute_cd.c\
		builtins/execute_pwd.c builtins/execute_exit.c \
		builtins/execute_env.c builtins/execute_export.c\
		builtins/execute_unset.c\
		# free.c error.c
		

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) lib_ft
	@ar rcs $(LIB) $(OBJ)
	$(CC) $(LIB)
	@echo "\n>>>>>Finished making<<<<<"

	gcc maran_execute/echo.c ft_strcmp.c libft/ft_strlen.c -o sophie_execute/echo
	@echo "\n>>>>>Finished making builtin executables<<<<<"

lib_ft:
	@make -C $(LIBFT)
	@make bonus -C $(LIBFT)
	@cp libft/libft.a ./$(LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -D BUFFER_SIZE=128

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	$(RM) $(LIB) a.out file* maran_execute/echo
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re