NAME = cub3D

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
# -fsanitize=address -g3

LIBFT_DIR = libs/libft
MLX_FLAGS = -lmlx -lXext -lX11 -lm
PARSER_DIR = parsing
RAYCASTING_DIR = raycasting
GC_DIR = garbage_collector

SRC = main.c \
	$(PARSER_DIR)/parsing.c \
	$(PARSER_DIR)/texture.c \
	$(PARSER_DIR)/color.c \
	$(PARSER_DIR)/parse_map.c \
	$(PARSER_DIR)/parse_utils.c \
	$(PARSER_DIR)/validation_map_utils.c \
	$(PARSER_DIR)/validation_map.c \
	$(PARSER_DIR)/parse_map_utils.c \
	$(RAYCASTING_DIR)/init_game.c \
	$(RAYCASTING_DIR)/draw_mini_map.c \
	$(RAYCASTING_DIR)/draw_gun.c \
	$(RAYCASTING_DIR)/clean_mlx.c \
	$(RAYCASTING_DIR)/player_rotation.c \
	$(RAYCASTING_DIR)/player_movment.c \
	$(RAYCASTING_DIR)/player_movment_utils.c \
	$(RAYCASTING_DIR)/init_player.c \
	$(RAYCASTING_DIR)/init_textures.c \
	$(RAYCASTING_DIR)/raycasting.c \
	$(RAYCASTING_DIR)/put_textures_on_wall.c \
	$(GC_DIR)/gc.c \
	$(GC_DIR)/ft_calloc_gc.c \
	$(GC_DIR)/ft_split_gc.c \
	$(GC_DIR)/ft_strdup_gc.c \
	$(GC_DIR)/ft_strndup.c \
	$(GC_DIR)/ft_strjoin_char_gc.c \
	$(GC_DIR)/ft_strjoin_gc.c \
	$(GC_DIR)/ft_strtrim_gc.c \
	$(GC_DIR)/ft_substr_gc.c \
	libs/get_next_line/get_next_line_bonus.c \
	libs/get_next_line/get_next_line_utils_bonus.c
OBJ = $(SRC:.c=.o)

INCLUDES = -I. -I$(PARSER_DIR) -I$(RAYCASTING_DIR) -I$(GC_DIR)
HEADER = cub3D.h

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
