NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror 
# -fsanitize=address -g3

LIBFT_DIR = libs/libft
MLX_DIR = libs/minilibx-linux
MLX_FLAGS = -L$(MLX_DIR) -lmlx -lXext -lX11 -lm
PARSER_DIR = parsing
RAYCASTING_DIR = raycasting

SRC = main.c \
	$(PARSER_DIR)/parsing.c \
	$(PARSER_DIR)/texture.c \
	$(PARSER_DIR)/color.c \
	$(PARSER_DIR)/parse_map.c \
	$(PARSER_DIR)/validation_map_utils.c \
	$(PARSER_DIR)/validation_map.c \
	$(RAYCASTING_DIR)/init_game.c \
	$(RAYCASTING_DIR)/draw_map.c \
	libs/get_next_line/get_next_line_bonus.c \
	libs/get_next_line/get_next_line_utils_bonus.c
OBJ = $(SRC:.c=.o)

INCLUDES = -I. -I$(PARSER_DIR) -I$(RAYCASTING_DIR)

HEADER = cub3d.h

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT_DIR)/libft.a
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)/libft.a -o $(NAME) $(MLX_FLAGS) $(INCLUDES)

$(LIBFT_DIR)/libft.a:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -f $(OBJ)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all
