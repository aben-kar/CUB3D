/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:48:39 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/16 12:30:48 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void raycast_3d(t_game *game)
{
    int x;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        cast_single_ray(game, camera_x);
        
        game->ray->line_height = (int)(SCREEN_HEIGHT / game->ray->perp_wall_dist);
        
        game->ray->draw_start = (SCREEN_HEIGHT / 2) - (game->ray->line_height / 2);
        game->ray->draw_end = (SCREEN_HEIGHT / 2) + (game->ray->line_height / 2);
        
        if (game->ray->draw_start < 0) // top texture
            game->ray->draw_start = 0;   
        if (game->ray->draw_end > SCREEN_HEIGHT) // buttom texture
            game->ray->draw_end = SCREEN_HEIGHT;
        draw_wall_column(game, x);
        x++;            
    }
    draw_gun(game);
}

int	get_tex_pixel_color(t_texture *tex, int x, int y)
{
	char	*pixel;

	if (x < 0 || x >= tex->width || y < 0 || y >= tex->height)
		return (0);
	pixel = tex->addr + (y * tex->line_len + x * (tex->bpp / 8));
	return (*(unsigned int *)pixel);
}


void draw_wall_column(t_game *game, int x)
{
    int y;
    int color;
    
    y = 0;
    while (y < game->ray->draw_start)
    {
        my_mlx_pixel_put(game, x, y, game->data->ceiling_color);
        y++;
    }

    t_texture *tex;
    int tex_x;
    int tex_y;
    double step;
    double tex_pos;
    double wall_x;

    if (game->ray->side == 0)
    {
        if (game->ray->ray_dir_x > 0)
            tex = &game->west;
        else
            tex = &game->east;  
    }
    else
    {
        if (game->ray->ray_dir_y > 0)
            tex = &game->north;
        else
            tex = &game->south;       
    }

    if (game->ray->side == 0)
        wall_x = game->player->y + game->ray->perp_wall_dist * game->ray->ray_dir_y;
    else
        wall_x = game->player->x + game->ray->perp_wall_dist * game->ray->ray_dir_x;

    wall_x -= floor(wall_x);

    tex_x = (int)(wall_x * tex->width);
    if ((game->ray->side == 0 && game->ray->ray_dir_x > 0)
        || (game->ray->side == 1 && game->ray->ray_dir_y < 0))
        tex_x = tex->width - tex_x - 1;

    step = 1.0 * tex->height / game->ray->line_height;
    tex_pos = (game->ray->draw_start - SCREEN_HEIGHT / 2 + game->ray->line_height / 2) * step;

    y = game->ray->draw_start;
    while (y <= game->ray->draw_end)
    {
        tex_y = (int)tex_pos & (tex->height - 1);
        tex_pos += step;
        color = get_tex_pixel_color(tex, tex_x, tex_y);
        my_mlx_pixel_put(game, x, y, color);
        y++;
    }
    
    y = game->ray->draw_end + 1;
    while (y < SCREEN_HEIGHT)
    {
        my_mlx_pixel_put(game, x, y, game->data->floor_color);
        y++;
    }
}
