NAME = fillit
CFLAGS = -Werror -Wextra -Wall
SRC_DIR = src
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

$(NAME): $(OBJ)
	make -C libft/ fclean
	make -C libft/
	clang -o $(NAME) $(CFLAGS) $(OBJ) -I libft -L libft/ -lft

%.o:%.c $(HEAD)
	clang $(CFLAGS) -I includes -I libft -c $(SRC)

clean:
	-rm -f *.o

fclean: clean
	-rm -f $(NAME)
	-rm -f *.out

re: fclean all