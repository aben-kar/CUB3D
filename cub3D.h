/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 22:40:39 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/28 20:20:10 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <mlx.h>
# include <X11/keysym.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdbool.h>
# include <math.h>
# include "garbage_collector/gc.h"
# include "libs/libft/libft.h"
# include "libs/get_next_line/get_next_line_bonus.h"

# define SCREEN_WIDTH 1000
# define SCREEN_HEIGHT 500
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define FOV 0.66
# define GUN_TRANSPARENT 0x000000
# define GUN_SCALE 3

typedef struct s_data	t_data;

typedef struct s_ray
{
	double	ray_dir_x;
	double	ray_dir_y;
	int		map_x;
	int		map_y;
	double	side_dist_x;
	double	side_dist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	int		step_x;
	int		step_y;
	int		hit;
	int		side;
	double	perp_wall_dist;
	int		line_height;
	int		draw_start;
	int		draw_end;
}	t_ray;

typedef struct s_player
{
	double	x;
	double	y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	move_speed;
	double	rot_speed;
	double	angle;
}	t_player;

typedef struct s_texture
{
	void	*img;
	char	*addr;
	int		width;
	int		height;
	int		bpp;
	int		line_len;
	int		endian;
}	t_texture;

typedef struct s_texture_data
{
	int		y;
	int		color;
	double	step;
	double	tex_pos;
}	t_texture_data;

typedef struct s_game
{
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			map_rows;
	double		player_x;
	double		player_y;
	int			mv_forward;
	int			mv_backward;
	int			mv_left;
	int			mv_right;
	int			rot_left;
	int			rot_right;
	t_data		*data;
	t_player	*player;
	t_ray		*ray;
	t_texture	north;
	t_texture	south;
	t_texture	east;
	t_texture	west;
	t_texture	gun_idle;
	t_texture	gun_fire;
	int			shooting;
	int			draw_color;
	int			map_fd;
	char		*current_gnl_line;
	t_gc		*gc;
}	t_game;

typedef struct s_data_gun
{
	int	gx;
	int	gy;
	int	color;
	int	start_x;
	int	start_y;
}	t_data_gun;

typedef struct s_data
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	int		floor_color;
	int		ceiling_color;
	char	**map;
}	t_data;

typedef struct s_mapinfo
{
	char	**src;
	int		lines;
	int		cols;
}	t_mapinfo;

void	parsing_cub(t_data *data, int fd, t_game *game);
void	parse_texture_and_color(t_data *data, int fd, t_game *game);
void	parse_config_file(t_data *data, char *line, t_game *game, char *line1);
int		all_config_parsed(t_data *data);
int		extract_rgb_color(char *line, t_game *game);
void	free_split(char **split);
void	print_error_and_exit(const char *msg, t_game *game);
void	parse_map(t_data *data, int fd, t_game *game);
void	parse_color(t_data *data, char **str, t_game *game);
int		is_map_line(char *line);
void	is_map_valid(t_data *data, t_game *game);
void	check_multiple_player(t_data *data, t_game *game);
void	is_map_closed(char **map, t_game *game);
bool	is_player(char position);
void	parse_texture(t_data *data, char **str, t_game *game);
void	check_map_line(char *map_joined, char *line, t_game *game);
void	check_empty_line_in_map(char *map_joined, char *line, t_game *game);
void	init_game(t_game *game);
void	draw_mini_map(t_game *game);
void	init_player(t_game *game);
void	init_textures(t_game *game);
int		close_window(t_game *game);
int		key_press(int keycode, t_game *game);
int		render_frame(t_game *game);
void	movment_player(int key, t_game *game);
int		is_valid_position(t_game *game, double x, double y);
int		is_valid_position_with_buffer(t_game *game, double x, double y);
void	rotate_player_right(t_player *player);
void	rotate_player_left(t_player *player);
int		key_release(int key, t_game *game);
int		mouse_press(int button, int x, int y, t_game *game);
int		mouse_release(int button, int x, int y, t_game *game);
int		mouse_move(int x, int y, t_game *game);
void	raycast_3d(t_game *game);
void	my_mlx_pixel_put(t_game *game, int x, int y, int color);

void	draw_wall_column(t_game *game, int x);
void	cast_single_ray(t_game *game, double camera_x);
int		get_tex_pixel_color(t_texture *tex, int x, int y);
void	draw_gun(t_game *game);
void	destroy_textures(t_game *game);
void	cleanup_gnl(int fd);
void	cleanup_and_exit(t_game *game, int exit_code);
void	zero_texture_structs(t_game *game);

#endif