/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:11:51 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/06 23:45:29 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

#include "libs/minilibx-linux/mlx.h"
# include <X11/keysym.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "garbage_collector/gc.h"
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
#define FOV 0.66

typedef struct s_data t_data;

typedef struct s_ray
{
    // Ray direction
    double ray_dir_x;           // Direction X dyal ray
    double ray_dir_y;           // Direction Y dyal ray
    
    // Map position (cell li fih player)
    int map_x;              // X coordinate f map
    int map_y;              // Y coordinate f map
    
    // Side distance (distance mn player l next grid line)
    double side_dist_x;     // Distance l vertical grid line
    double side_dist_y;     // Distance l horizontal grid line
    
    // Delta distance (distance bin grid lines)
    double delta_dist_x;    // Distance bin vertical lines
    double delta_dist_y;    // Distance bin horizontal lines
    
    // Step direction (-1 or +1)
    int step_x;             // Direction f X (-1 = shimale, +1 = limen)
    int step_y;             // Direction f Y (-1 = lfou9, +1 = louta7)
    
    // Wall hit info
    int hit;                // Wach l9a wall? (0 = no, 1 = yes)
    int side;               // Ashmen side hit? (0 = vertical, 1 = horizontal)
    
    // Distance to wall
    double perp_wall_dist;  // Perpendicular distance l wall
    
    // Wall rendering info
    int line_height;        // Height dyal wall line f screen
    int draw_start;         // Fin tبدا ترسم wall (pixel Y)
    int draw_end;           // Fin تسالي ترسم wall (pixel Y)
    
} t_ray;

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

typedef struct s_texture
{
    void    *img;
    char    *addr;
    int     width;
    int     height;
    int     bpp;
    int     line_len;
    int     endian;
}   t_texture;

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
    //////////
    int mv_forward;
    int mv_backward;
    int mv_left;
    int mv_right;
    int rot_left;
    int rot_right;
    ////////////
    t_data *data;
    t_player *player;
    t_ray *ray;
    t_texture north;
    t_texture south;
    t_texture east;
    t_texture west;
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
void parsing_cub(t_data *data, int fd, t_gc **gc);
void parse_texture_and_color(t_data *data, int fd, t_gc **gc);
void parse_config_file(t_data *data, char *line, t_gc **gc);
int all_config_parsed(t_data *data);
int extract_rgb_color(char *line, t_gc **gc);
void free_split(char **split);
void print_error_and_exit(const char *msg);
void parse_map(t_data *data, int fd, t_gc **gc);
int is_map_line(char *line);
void is_map_valid(t_data *data, t_gc **gc);
void check_multiple_player(t_data *data);
void is_map_closed(char **map);
bool is_player(char position);

// function raycasting
void init_game(t_game *game);
void draw_mini_map(t_game *game);
void init_player(t_game *game);
void    init_textures(t_game *game);
int close_window(t_game *game);
int key_press(int keycode, t_game *game);
int render_frame(t_game *game);
// void rotation_player(int key, t_player *player);
void movment_player(int key, t_game *game);
void rotate_player_right(t_player *player);
void rotate_player_left(t_player *player);
int key_release(int key, t_game *game);
void raycast_3d(t_game *game);
void my_mlx_pixel_put(t_game *game, int x, int y, int color);


void ray_mlx_pixel_put(t_game *game, int x, int y, int color);
void draw_wall_column(t_game *game, int x);
void cast_single_ray(t_game *game, double camera_x);

#endif