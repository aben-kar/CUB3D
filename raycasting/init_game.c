/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:05:00 by achraf            #+#    #+#             */
/*   Updated: 2025/10/19 17:29:11 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void    init_mlx(t_game *game)
{
    if (!game)
        return ;
    game->mlx = mlx_init();
    if (!game->mlx)
        print_error_and_exit("Failed to initialize MLX", game);
    game->mlx_win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
    if (!game->mlx_win)
        print_error_and_exit("Failed to create window", game);
    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    if (!game->img)
        print_error_and_exit("Failed to create image", game);
    game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel, &game->line_length, &game->endian);
    if (!game->addr)
        print_error_and_exit ("Failed to get image data address", game);
}

void init_mlx_game(t_game *game)
{
    if (!game)
        return;

    init_mlx(game);    
    mlx_hook(game->mlx_win, 2, 1L<<0, key_press, game);
    mlx_hook(game->mlx_win, 3, 1L<<1, key_release, game);
    mlx_hook(game->mlx_win, 4, 1L << 2, mouse_press, game);
    mlx_hook(game->mlx_win, 5, 1L << 3, mouse_release, game);
    mlx_hook(game->mlx_win, 6, 1L<<6, mouse_move, game);
    mlx_loop_hook(game->mlx, render_frame, game);
    mlx_hook(game->mlx_win, 17, 1L<<17, close_window, game);
    draw_mini_map(game);
    init_textures(game);
    mlx_loop(game->mlx);
}

void init_game(t_game *game)
{
    init_player(game);
    init_mlx_game(game);
}