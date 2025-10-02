/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-kar <aben-kar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:11:02 by aben-kar          #+#    #+#             */
/*   Updated: 2025/10/02 22:17:21 by aben-kar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void rotate_player_left(t_player *player)
{
    double speed_rotation = player->rot_speed;

    player->angle -= speed_rotation;
    player->dir_x = cos(player->angle);
    player->dir_y = sin(player->angle);
}

void rotate_player_right(t_player *player)
{
    double speed_rotation = player->rot_speed;

    player->angle += speed_rotation;
    player->dir_x = cos(player->angle);
    player->dir_y = sin(player->angle);
}

// void rotation_player(int key, t_player *player)
// {
//     if (key == KEY_LEFT)  // Flèche gauche
//         rotate_player_left(player);
//     if (key == KEY_RIGHT) // Flèche droite
//         rotate_player_right(player);
// }