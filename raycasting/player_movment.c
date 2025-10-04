/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:59:33 by aben-kar          #+#    #+#             */
/*   Updated: 2025/10/03 18:03:55 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int is_wall(t_game *game, double x, double y)
{
    int map_x;
    int map_y;

    map_x = (int)x;
    map_y = (int)y;

    // Vérifier hors carte
    if (map_y < 0 || map_y >= game->map_rows ||
        map_x < 0 || map_x >= (int)ft_strlen(game->data->map[map_y]))
        return (1);

    // Vérifier mur
    if (game->data->map[map_y][map_x] == '1')
        return (1);

    return (0);
}

void movment_player(int key, t_game *game)
{
    double new_x;
    double new_y;
    double move_speed;

    new_x = game->player->x;
    new_y = game->player->y;
    move_speed = game->player->move_speed;

    if (key == KEY_W)
    {
        new_x = game->player->x + game->player->dir_x * move_speed;
        new_y = game->player->y + game->player->dir_y * move_speed;
    }
    else if (key == KEY_S)
    {
        new_x = game->player->x - game->player->dir_x * move_speed;
        new_y = game->player->y - game->player->dir_y * move_speed;
    }
    else if (key == KEY_D)
    {
        new_x = game->player->x - game->player->dir_y * move_speed;
        new_y = game->player->y + game->player->dir_x * move_speed;
    }
    else if (key == KEY_A)
    {
        new_x = game->player->x + game->player->dir_y * move_speed;
        new_y = game->player->y - game->player->dir_x * move_speed;
    }
    else if (key == KEY_LEFT)  // Flèche gauche
        rotate_player_left(game->player);
    else if (key == KEY_RIGHT) // Flèche droite
        rotate_player_right(game->player);
    if (!is_wall(game, new_x, game->player->y)) // Check x direction
    {
        game->player->x = new_x;
        game->player->y = new_y;
    }
}