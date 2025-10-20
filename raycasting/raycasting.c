/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:48:39 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/20 15:46:33 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	init_ray(t_game *game, double camera_x)
{
	game->ray->ray_dir_x = game->player->dir_x
		+ game->player->plane_x * camera_x;
	game->ray->ray_dir_y = game->player->dir_y
		+ game->player->plane_y * camera_x;
	game->ray->map_x = (int)game->player->x;
	game->ray->map_y = (int)game->player->y;
	game->ray->delta_dist_x = fabs(1.0 / game->ray->ray_dir_x);
	game->ray->delta_dist_y = fabs(1.0 / game->ray->ray_dir_y);
	game->ray->hit = 0;
}

void	get_side_disit(t_game *game)
{
	if (game->ray->ray_dir_x < 0)
	{
		game->ray->step_x = -1;
		game->ray->side_dist_x = (game->player->x - game->ray->map_x)
			* game->ray->delta_dist_x;
	}
	else
	{
		game->ray->step_x = 1;
		game->ray->side_dist_x = (game->ray->map_x + 1.0 - game->player->x)
			* game->ray->delta_dist_x;
	}
	if (game->ray->ray_dir_y < 0)
	{
		game->ray->step_y = -1;
		game->ray->side_dist_y = (game->player->y - game->ray->map_y)
			* game->ray->delta_dist_y;
	}
	else
	{
		game->ray->step_y = 1;
		game->ray->side_dist_y = (game->ray->map_y + 1.0 - game->player->y)
			* game->ray->delta_dist_y;
	}
}

void	dda_algorithme(t_game *game)
{
	while (game->ray->hit == 0)
	{
		if (game->ray->side_dist_x < game->ray->side_dist_y)
		{
			game->ray->side_dist_x += game->ray->delta_dist_x;
			game->ray->map_x += game->ray->step_x;
			game->ray->side = 0;
		}
		else
		{
			game->ray->side_dist_y += game->ray->delta_dist_y;
			game->ray->map_y += game->ray->step_y;
			game->ray->side = 1;
		}
		if (game->data->map[game->ray->map_y][game->ray->map_x] == '1')
			game->ray->hit = 1;
	}
}

void	cast_single_ray(t_game *game, double camera_x)
{
	init_ray(game, camera_x);
	get_side_disit(game);
	dda_algorithme(game);
	if (game->ray->side == 0)
	{
		game->ray->perp_wall_dist = (game->ray->map_x - game->player->x
				+ (1 - game->ray->step_x) / 2) / game->ray->ray_dir_x;
	}
	else
	{
		game->ray->perp_wall_dist = (game->ray->map_y - game->player->y
				+ (1 - game->ray->step_y) / 2) / game->ray->ray_dir_y;
	}
}

void	raycast_3d(t_game *game)
{
	int		x;
	double	camera_x;

	x = 0;
	while (x < SCREEN_WIDTH)
	{
		camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
		cast_single_ray(game, camera_x);
		game->ray->line_height = (int)(SCREEN_HEIGHT
				/ game->ray->perp_wall_dist);
		game->ray->draw_start = (SCREEN_HEIGHT / 2)
			- (game->ray->line_height / 2);
		game->ray->draw_end = (SCREEN_HEIGHT / 2)
			+ (game->ray->line_height / 2);
		if (game->ray->draw_start < 0)
			game->ray->draw_start = 0;
		if (game->ray->draw_end > SCREEN_HEIGHT)
			game->ray->draw_end = SCREEN_HEIGHT;
		draw_wall_column(game, x);
		x++;
	}
	draw_gun(game);
}
