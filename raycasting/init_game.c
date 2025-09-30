/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:05:00 by achraf            #+#    #+#             */
/*   Updated: 2025/09/29 18:04:21 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void init_game(t_game *game)
{
    // Initialize MLX
    game->mlx = mlx_init();
    if (!game->mlx)
    {
        printf("Error\nFailed to initialize MLX\n");
        exit(1);
    }
    
    // Create window
    game->win = mlx_new_window(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT, "CUB3D");
    if (!game->win)
    {
        printf("Error\nFailed to create window\n");
        exit(1);
    }
    
    // Initialize player position (we'll set this properly later when we have map data)
    game->player_x = 5.0;
    game->player_y = 5.0;
    game->dir_x = -1.0;
    game->dir_y = 0.0;
    game->plane_x = 0.0;
    game->plane_y = 0.66;
    game->move_speed = 0.05;
    game->rot_speed = 0.03;
    
    printf("Game initialized successfully!\n");
    printf("Window size: %dx%d\n", SCREEN_WIDTH, SCREEN_HEIGHT);
    printf("Player position: (%.1f, %.1f)\n", game->player_x, game->player_y);
    
    // Simple game loop for now
    mlx_loop(game->mlx);
}