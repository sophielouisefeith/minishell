# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: Maran <Maran@student.codam.nl>               +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/06 17:19:34 by Maran         #+#    #+#                  #
#    Updated: 2020/07/06 17:58:55 by Maran         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LIB = minishell.a

LIBFT = libft

SRC =  parser.c\
		get_next_line/get_next_line.c get_next_line/get_next_line_utils.c\

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) lib_ft
	@ar rcs $(LIB) $(OBJ)
	$(CC) $(LIB)
	@echo "\n>>>>>Finished making<<<<<"

lib_ft:
	@make -C $(LIBFT)
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