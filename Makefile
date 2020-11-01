# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sfeith <sfeith@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2020/08/24 16:17:15 by sfeith        #+#    #+#                  #
#    Updated: 2020/11/01 17:05:42 by sfeith        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = minishell.a

LIBFT = libft

SRC =  srcs/main.c\
		srcs/utils/signals.c srcs/utils/save_env.c\
		srcs/utils/character_check.c\
		srcs/utils/character_check2.c\
		srcs/utils/free.c\
		srcs/lexer/lexer.c srcs/lexer/lexer_utils.c\
		srcs/lexer/ll_make_list_lexer.c\
		libft/get_next_line/get_next_line.c\
		libft/get_next_line/get_next_line_utils.c\
		srcs/parser/parser.c\
		srcs/parser/parser_utils.c\
		srcs/parser/ll_make_list_parser.c\
		srcs/parser/input.c\
		srcs/parser/output.c\
		srcs/parser/free_parser.c\
		srcs/execute/execute.c\
		srcs/execute/execute_utils.c\
		execute/check_specials.c\
		srcs/execute/check_specials_utils.c\
		srcs/execute/execute_builtin.c\
		srcs/builtin/echo.c\
		srcs/execute/execute_cd.c  srcs/execute/execute_pwd.c\
		srcs/execute/env_ll_to_array.c\
		srcs/execute/env.c\
		srcs/execute/execute_unset.c\
		srcs/execute/execute_exit.c\
		srcs/execute/parameter_expansion.c\
		srcs/execute/parameter_expansion_utils.c\
		srcs/execute/execute_export.c\
		srcs/execute/ft_split2.c\
		get_path.c\
		srcs/utils/error.c\
		srcs/utils/error_utils.c\
		srcs/execute/check_builtin_again.c\
		srcs/execute/execute_export_utils.c\

OBJ = $(SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror -fsanitize=address -g
#-fsanitize=address -g

INCL = includes

all: $(NAME)

# -fsanitize=address -g3
# -ggdb3
# -g -fsanitize=address -O1 -fno-omit-frame-pointer

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
	$(CC) $(CFLAGS) -I$(INCL) -c $< -o $@

clean:
	$(RM) $(OBJ)
	@make clean -C $(LIBFT)

fclean: clean
	@$(RM) $(LIB) a.out
	@make fclean -C $(LIBFT)

re: fclean all

.PHONY: all clean fclean re