# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Maran <Maran@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/06 17:19:34 by Maran         #+#    #+#                  #
#    Updated: 2020/08/20 12:17:19 by maran         ########   odam.nl          #
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
		maran_execute/execute_maran.c\
		maran_execute/execute_builtin.c\
		maran_execute/execute_maran.c\
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
	$(RM) $(LIB) a.out
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re