NAME = cub3d

CC = cc
CFLAGS = -Wall -Wextra -Werror 

LIBFT_DIR = libft

SRC = main.c check_texture_and_color.c check_T_and_C_utils.c get_next_line/get_next_line_bonus.c get_next_line/get_next_line_utils_bonus.c
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
