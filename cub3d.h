/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:11:51 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/03 16:52:28 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include "libs/minilibx-linux/mlx.h"
# include <X11/keysym.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "libs/libft/libft.h"
#include "libs/get_next_line/get_next_line_bonus.h"


#define SCREEN_WIDTH 1000
#define SCREEN_HEIGHT 500
#define KEY_ESC 65307
#define KEY_W 119
#define KEY_A 97
#define KEY_S 115
#define KEY_D 100
#define KEY_LEFT 65361
#define KEY_RIGHT 65363
#define FOV 1,0472

typedef struct s_data t_data;

typedef struct s_player {
    double x;          // Position x dyal player
    double y;          // Position y dyal player
    double dir_x;      // Direction vector x
    double dir_y;      // Direction vector y
    double plane_x;    // Camera plane x (FOV)
    double plane_y;    // Camera plane y (FOV)
    double move_speed; // Vitesse dyal movement
    double rot_speed;  // Vitesse dyal rotation
    double angle;      // Angle dyal player
} t_player;

typedef struct s_game
{
    void    *mlx;
    void    *mlx_win;
    void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
    int     map_rows;
    double  player_x;
    double  player_y;
    t_data *data;
    t_player *player;;
}   t_game;

typedef struct s_data
{
    char *path_no;
    char *path_so;
    char *path_we;
    char *path_ea;
    int floor_color;
    int ceiling_color;
    char **map;
} t_data;


// Function parsing
void parsing_cub(t_data *data, int fd);
void parse_texture_and_color(t_data *data, int fd);
void parse_config_file(t_data *data, char *line);
int all_config_parsed(t_data *data);
int extract_rgb_color(char *line);
void free_split(char **split);
void print_error_and_exit(const char *msg);
void parse_map(t_data *data, int fd);
int is_map_line(char *line);
void is_map_valid(t_data *data);
void check_multiple_player(t_data *data);
void is_map_closed(char **map);
bool is_player(char position);

// function raycasting
void init_game(t_game *game);
void draw_mini_map(t_game *game);
void init_player(t_game *game);
int close_window(t_game *game);
int key_press(int keycode, t_game *game);
int render_frame(t_game *game);
// void rotation_player(int key, t_player *player);
void movment_player(int key, t_game *game);
void rotate_player_right(t_player *player);
void rotate_player_left(t_player *player);

#endif