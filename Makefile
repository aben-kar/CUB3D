NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror 
# -fsanitize=address -g3

LIBFT_DIR = libs/libft

SRC = main.c parsing.c texture.c color.c parse_map.c libs/get_next_line/get_next_line_bonus.c libs/get_next_line/get_next_line_utils_bonus.c
OBJ = $(SRC:.c=.o)

# MLX = ./mlx
# MLX_FLAGS = -L$(MLX) -lmlx -framework OpenGL -framework AppKit

HEADER = cub3d.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)/libft.a -o $(NAME)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
