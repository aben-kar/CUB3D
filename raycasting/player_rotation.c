/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:11:02 by aben-kar          #+#    #+#             */
/*   Updated: 2025/10/03 16:52:09 by acben-ka         ###   ########.fr       */
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
