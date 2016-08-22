# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aljourda <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/01/11 15:29:27 by aljourda          #+#    #+#              #
#    Updated: 2016/08/16 14:05:34 by aljourda         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=fdf
SRC= get_next_line/get_next_line.c \
		srcs/integer.c \
		srcs/camera.c \
		srcs/graphics.c \
		srcs/map.c \
		srcs/fdf.c

CC=clang
CFLAGS=-I libft/includes -I minilibx_macos/ -I get_next_line/ -I includes/ -Wall -Wextra -Werror
OBJ=$(SRC:.c=.o)
LDFLAGS=-L libft/ -L minilibx_macos/
LIBS=-lft -lm -lmlx -framework OpenGL -framework AppKit

$(NAME): $(OBJ)
	make -C libft/
	make -C minilibx_macos/
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS) $(LIBS)

all: $(NAME)

clean:
	make clean -C libft/
	make clean -C minilibx_macos/
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

%.o: %.c
	$(CC) -c $(CFLAGS) $^ -o $@
