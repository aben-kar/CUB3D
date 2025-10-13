/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:46:15 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/06 23:48:42 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_ray(t_game *game, double camera_x)
{
    game->ray->ray_dir_x = game->player->dir_x + game->player->plane_x * camera_x;
    game->ray->ray_dir_y = game->player->dir_y + game->player->plane_y * camera_x;

    game->ray->map_x = (int)game->player->x;
    game->ray->map_y = (int)game->player->y;

    game->ray->delta_dist_x = fabs(1.0 / game->ray->ray_dir_x);
    game->ray->delta_dist_y = fabs(1.0 / game->ray->ray_dir_y);
    
    game->ray->hit = 0; // was there a wall hit?
}

void get_side_disit(t_game *game)
{
    if (game->ray->ray_dir_x < 0)
    {
        game->ray->step_x = -1;  // Nemchiw l ysar
        game->ray->side_dist_x = (game->player->x - game->ray->map_x) * game->ray->delta_dist_x;
    }
    else
    {
        game->ray->step_x = 1;   // Nemchiw l ymin
        game->ray->side_dist_x = (game->ray->map_x + 1.0 - game->player->x) * game->ray->delta_dist_x;
    }
        
    if (game->ray->ray_dir_y < 0)
    {
        game->ray->step_y = -1;  // Nemchiw l fo9
        game->ray->side_dist_y = (game->player->y - game->ray->map_y) * game->ray->delta_dist_y;
    }
    else
    {
        game->ray->step_y = 1;   // Nemchiw l te7t
        game->ray->side_dist_y = (game->ray->map_y + 1.0 - game->player->y) * game->ray->delta_dist_y;
    } 
}

void dda_algorithme(t_game *game)
{
    while (game->ray->hit == 0)
    {
            // Nchofo: X wla Y 9rib?
        if (game->ray->side_dist_x < game->ray->side_dist_y)
        {
                // X 9rib, nemchiw f direction X
            game->ray->side_dist_x += game->ray->delta_dist_x;
            game->ray->map_x += game->ray->step_x;
            game->ray->side = 0;  // Vertical wall
        }
        else
        {
                // Y 9rib, nemchiw f direction Y
            game->ray->side_dist_y += game->ray->delta_dist_y;
            game->ray->map_y += game->ray->step_y;
            game->ray->side = 1;  // Horizontal wall
        }
            
            // Nchofo: wach drebna f wall?
        if (game->data->map[game->ray->map_y][game->ray->map_x] == '1')
            game->ray->hit = 1;
    }
}

void cast_single_ray(t_game *game, double camera_x)
{
    init_ray(game, camera_x);
    get_side_disit(game);
    dda_algorithme(game);
    if (game->ray->side == 0)
    {
            // Vertical wall
        game->ray->perp_wall_dist = (game->ray->map_x - game->player->x + 
                                (1 - game->ray->step_x) / 2) / game->ray->ray_dir_x;
    }
    else
    {
            // Horizontal wall
        game->ray->perp_wall_dist = (game->ray->map_y - game->player->y + 
                                (1 - game->ray->step_y) / 2) / game->ray->ray_dir_y;
    }
}

void    draw_gun(t_game *game)
{
	t_texture *gun;
	int start_x;
	int start_y;
	int gx;
	int gy;
	int color;
    int	sx;
	int	sy;

	// choose gun texture
	if (game->shooting)
    {
        gun = &game->gun_idle;
    }
    else
    {
        gun = &game->gun_fire;
    }
	
    if (!gun || !gun->img || !gun->addr)
		return;

    int scaled_width = gun->width * GUN_SCALE;
	int scaled_height = gun->height * GUN_SCALE;
	// position: bottom-centered
	start_x = (SCREEN_WIDTH / 2) - (scaled_width / 2);
	start_y = SCREEN_HEIGHT - scaled_height;
	if (start_x < 0) start_x = 0;
	if (start_y < 0) start_y = 0;

	gy = 0;
	while (gy < gun->height)
	{
		gx = 0;
		while (gx < gun->width)
		{
            sx = gx / (double)GUN_SCALE;
			sy = gy / (double)GUN_SCALE;
			color = get_tex_pixel_color(gun, gx, gy);
			// skip transparent pixels (use color key)
			if ((color & 0x00FFFFFF) != (GUN_TRANSPARENT & 0x00FFFFFF))
				my_mlx_pixel_put(game, start_x + gx, start_y + gy, color);
			gx++;
		}
		gy++;
	}
}
