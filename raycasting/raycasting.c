/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:48:39 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/06 23:44:15 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void raycast_3d(t_game *game)
{
    int x;

    x = 0;
    while (x < SCREEN_WIDTH)
    {
        double camera_x = 2 * x / (double)SCREEN_WIDTH - 1;
        cast_single_ray(game, camera_x);
        
        game->ray->line_height = (int)(SCREEN_HEIGHT / game->ray->perp_wall_dist);

        game->ray->draw_start = -game->ray->line_height / 2 + SCREEN_HEIGHT / 2;
        if (game->ray->draw_start < 0)
            game->ray->draw_start = 0;
            
        game->ray->draw_end = game->ray->line_height / 2 + SCREEN_HEIGHT / 2;
        if (game->ray->draw_end >= SCREEN_HEIGHT)
            game->ray->draw_end = SCREEN_HEIGHT - 1;
        draw_wall_column(game, x);
        x++;            
    }
}

void ray_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    // Verifi belli ma khrejnach men screen
    if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
        return;
    
    // N7esbo position f memory buffer
    dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
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
    
    if (game->ray->side == 0)
    {
        color = 0x00FF0000;
    }
    else
    {
        color = 0x00AA0000;
    }
    
    y = game->ray->draw_start;
    while (y <= game->ray->draw_end)
    {
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