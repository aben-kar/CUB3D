NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
# -fsanitize=address -g3

LIBFT_DIR = libs/libft
MLX_FLAGS = -lmlx -lXext -lX11 -lm
# MLX_DIR = minilibx-linux

SRC = main.c parsing.c texture.c color.c parse_map.c validation_map_utils.c validation_map.c libs/get_next_line/get_next_line_bonus.c libs/get_next_line/get_next_line_utils_bonus.c
OBJ = $(SRC:.c=.o)

# MLX_FLAGS = -lXext -lX11 -lm
# MLX_SRC = $(MLX_DIR)/mlx_init.c $(MLX_DIR)/mlx_new_window.c $(MLX_DIR)/mlx_pixel_put.c $(MLX_DIR)/mlx_loop.c $(MLX_DIR)/mlx_hook.c $(MLX_DIR)/mlx_key_hook.c
# MLX_OBJ = $(MLX_SRC:.c=.o)

HEADER = cub3d.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)/libft.a -o $(NAME) $(MLX_FLAGS)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

# %.o: %.c $(HEADER)
# 	$(CC) $(CFLAGS) -I$(MLX_DIR) -c $< -o $@

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
# 	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
# 	$(MAKE) -C $(MLX_DIR) clean
	rm -f $(NAME)

re: fclean all
