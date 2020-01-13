# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mphobos <mphobos@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/12 15:20:15 by mphobos           #+#    #+#              #
#    Updated: 2020/01/13 15:07:18 by mphobos          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_select
C = main.c list.c display_str.c free.c
SRC = $(patsubst %,src/%,$(C))
CC = gcc
INCLUDE = includes
CFLAGS = -Wall -Wextra -Werror -L libft -lft -ltermcap -I $(INCLUDE) -o $(NAME)
DFLAGS = $(CFLAGS) -g

%.c:
	$(CC) $(SRC) $(DFLAGS) -c $<

$(NAME): $(SRC)
	make -C libft
	$(CC) $(SRC) $(DFLAGS)

all: $(NAME)

clean:
	make -C libft clean

fclean: clean
	make -C libft fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
