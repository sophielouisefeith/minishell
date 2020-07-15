# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: SophieLouiseFeith <SophieLouiseFeith@st      +#+                      #
#                                                    +#+                       #
#    Created: 2020/07/08 13:02:04 by SophieLouis   #+#    #+#                  #
#    Updated: 2020/07/15 13:36:58 by SophieLouis   ########   odam.nl          #
#                                                                              #
# **************************************************************************** #


NAME = minishell

LIBFT = libft

SRC = error.c main.c utilitise.c parser.c
OBJ = $(SRC:.c=.o)
FLAGS = -Wall -Wextra -Werror -o minishell

all: $(NAME)

$(NAME): $(OFILE)
	@make -C $(LIBFT)
	@cp libft/libft.a ./$(NAME)
	@ar rcs $(NAME) $(OFILE)
	gcc $(FLAGS) $(SRC)

clean:
	$(RM) $(OBJ) -f $(OFILE)
	@make clean -C $(LIBFT)

fclean: clean
	$(RM) $(NAME)
	@make clean -C $(LIBFT)
	

re: fclean all

