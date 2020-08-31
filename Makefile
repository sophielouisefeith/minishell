# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sfeith <sfeith@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/24 16:17:15 by sfeith        #+#    #+#                  #
#    Updated: 2020/08/31 17:49:53 by maran         ########   odam.nl          #
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
		execute/execute_builtin.c\
		execute/echo.c\
		execute/execute_cd.c  execute/execute_pwd.c\
		execute/env_ll_to_array.c\
		execute/env.c\
		execute/execute_unset.c\
		execute/execute_exit.c\
		execute/parameter_expansion.c\
		execute/execute_export.c\
		execute/ft_split2.c\
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
	$(RM) $(LIB) a.out file* execute/echo execute/env
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re