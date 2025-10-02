/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-kar <aben-kar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:23:04 by aben-kar          #+#    #+#             */
/*   Updated: 2025/10/02 22:44:22 by aben-kar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int key_press(int key, t_game *game)
{
    if (!game || !game->player)
        return (0);
    movment_player(key, game);
    // rotation_player(key, game->player);
    draw_mini_map(game);
    return (0);
}

char find_position_player(t_game *game)
{
    int i, j;
    char player_char = 0;

    for (i = 0; game->data->map[i]; i++)
    {
        for (j = 0; game->data->map[i][j]; j++)
        {
            if (game->data->map[i][j] == 'N' || game->data->map[i][j] == 'S' ||
                game->data->map[i][j] == 'E' || game->data->map[i][j] == 'W')
            {
                game->player->x = j + 0.5; // Center dyal cell
                game->player->y = i + 0.5; // Center dyal cell
                player_char = game->data->map[i][j];
                return (player_char);
            }
        }
    }
    return (player_char);
}

void init_player(t_game *game)
{
    char player_char = find_position_player(game);
    
    if (player_char == 'N')
        game->player->angle = M_PI / 2.0;
    else if (player_char == 'S')
        game->player->angle = 3 * M_PI / 2.0;
    else if (player_char == 'W')
        game->player->angle = M_PI;
    else if (player_char == 'E')
        game->player->angle = 0.0;

    game->dir_x = cos(game->player->angle);
    game->dir_y = sin(game->player->angle);
    game->player->move_speed = 0.05;
    game->player->rot_speed = 0.03; 
}