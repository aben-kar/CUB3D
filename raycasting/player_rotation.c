/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 14:57:45 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/31 14:57:46 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	rotate_player_left(t_player *player)
{
	double	speed_rotation;

	speed_rotation = player->rot_speed;
	player->angle -= speed_rotation;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -player->dir_y * FOV;
	player->plane_y = player->dir_x * FOV;
}

void	rotate_player_right(t_player *player)
{
	double	speed_rotation;

	speed_rotation = player->rot_speed;
	player->angle += speed_rotation;
	player->dir_x = cos(player->angle);
	player->dir_y = sin(player->angle);
	player->plane_x = -player->dir_y * FOV;
	player->plane_y = player->dir_x * FOV;
}
