/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-kar <aben-kar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:05:00 by achraf            #+#    #+#             */
/*   Updated: 2025/10/02 16:53:01 by aben-kar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_mlx_game(t_game *game)
{
    if (!game)
        return;
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error\nFailed to initialize MLX\n");
        exit(1);
    }
    
    game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
    if (!game->mlx_win)
    {
        printf("Error\nFailed to create window\n");
        exit(1);
    }
    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game->img)
    {
        printf("Error\nFailed to create image\n");
        exit(1);
    }
    game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
    if (!game->addr)
    {
        printf("Error\nFailed to get image data address\n");
        exit(1);
    }
    mlx_hook(game->mlx_win, 2, 1L<<0, key_press, game); // Key press
    mlx_hook(game->mlx_win, 17, 1L<<17, close_window, game); // Close button
    mlx_loop_hook(game->mlx, render_frame, game);
    draw_mini_map(game);
    mlx_loop(game->mlx);
}


void init_game(t_game *game)
{
    init_player(game);
    init_mlx_game(game);
}