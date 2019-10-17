# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mmanhack <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/17 19:23:32 by mmanhack          #+#    #+#              #
#    Updated: 2019/10/17 19:23:34 by mmanhack         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = fillit
CFLAGS = -Werror -Wextra -Wall
SRC_DIR = src
LIBFT = libft/libft.a
OBJ_DIR = .
SRC = $(SRC_DIR)/ft_check_buffer.c \
      $(SRC_DIR)/ft_fill_square.c \
      $(SRC_DIR)/ft_out_on_terminal.c \
      $(SRC_DIR)/ft_reader_and_tab_maker.c \
      $(SRC_DIR)/main.c
HEAD = includes/fillit.h
OBJ = $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	gcc -o $(NAME) $(CFLAGS) $(OBJ) -I libft -L libft/ -lft

$(LIBFT):
	make -C libft

$(OBJ_DIR)/%.o:$(SRC_DIR)/%.c $(HEAD)
	gcc $(CFLAGS) -I. -I includes -I libft -c $< -o $@

clean:
	-rm -f $(OBJ)
	make -C libft clean

fclean: clean
	-rm -f $(NAME)
	-rm -f *.out
	make -C libft fclean

re: fclean all
