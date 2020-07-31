# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Maran <Maran@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/06 17:19:34 by Maran         #+#    #+#                  #
<<<<<<< HEAD
#    Updated: 2020/07/30 14:27:41 by maran         ########   odam.nl          #
=======
#    Updated: 2020/07/31 09:45:47 by SophieLouis   ########   odam.nl          #
>>>>>>> 9a44c0907cdcc4c8d7c15f6c0cf8505d35fb12c4
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = minishell.a

LIBFT = libft

SRC =  main.c lexer.c lexer_utils.c ft_strcmp.c\
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\
		ll_make_list.c transform.c builtin.c transform_check.c\
		builtins/execute.c builtins/execute_cd.c builtins/execute_pwd.c\
		builtins/execute_env.c builtins/execute_export.c\
		builtins/execute_unset.c output.c input.c\

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