# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: sfeith <sfeith@student.oodam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 20191028 14:14:30 by sfeith         #+#    #+#                 #
#    Updated: 20191106 15:08:29 by sfeith        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
FLAGS = -Wall -Werror -Wextra -I .

SRC = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c \
		ft_memmove.c ft_memchr.c ft_memcmp.c ft_strlen.c \
		ft_strnstr.c ft_atoi.c ft_isalpha.c \
		ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c \
		ft_toupper.c ft_tolower.c ft_strlcpy.c ft_strlcat.c \
		ft_calloc.c ft_strdup.c ft_strchr.c ft_strrchr.c \
		ft_strncmp.c ft_substr.c ft_strjoin.c ft_itoa.c \
		ft_putchar_fd.c  ft_strmapi.c ft_putstr_fd.c ft_split.c \
		ft_putendl_fd.c ft_putnbr_fd.c ft_strtrim.c 

BONUS_SRC = ft_lstnew_bonus.c ft_lstadd_front_bonus.c \
		ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c \
		ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c \
		ft_lstmap_bonus.c

OFILE = $(SRC:.c=.o)
BONUS_OFILE = $(BONUS_SRC:.c=.o)

all: $(NAME)

$(NAME): $(OFILE)
	ar rcs $(NAME) $(OFILE)

%.o: %.c
	gcc -c -g $(FLAGS) $< -o $@

bonus: $(NAME) $(BONUS_OFILE)
	ar rcs $(NAME) $(BONUS_OFILE)

clean:
	/bin/rm -f $(OFILE)
	/bin/rm -f $(BONUS_OFILE)

fclean: clean
	/bin/rm -f $(NAME)

re: fclean all
