/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 19:59:33 by aben-kar          #+#    #+#             */
/*   Updated: 2025/10/19 17:49:18 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void move_forward(t_game *game)
{
    double new_x;
    double new_y;
    
    new_x = game->player->x + game->player->dir_x * game->player->move_speed;
    new_y = game->player->y + game->player->dir_y * game->player->move_speed;
    
    if (is_valid_position_with_buffer(game, new_x, game->player->y))
        game->player->x = new_x;
    if (is_valid_position_with_buffer(game, game->player->x, new_y))
        game->player->y = new_y;
}

void move_backward(t_game *game)
{
    double new_x;
    double new_y;
    
    new_x = game->player->x - game->player->dir_x * game->player->move_speed;
    new_y = game->player->y - game->player->dir_y * game->player->move_speed;
    
    if (is_valid_position_with_buffer(game, new_x, game->player->y))
        game->player->x = new_x;
    if (is_valid_position_with_buffer(game, game->player->x, new_y))
        game->player->y = new_y;
}

void move_left(t_game *game)
{
    double new_x;
    double new_y;
    
    new_x = game->player->x - game->player->plane_x * game->player->move_speed;
    new_y = game->player->y - game->player->plane_y * game->player->move_speed;
    
    if (is_valid_position_with_buffer(game, new_x, game->player->y))
        game->player->x = new_x;
    if (is_valid_position_with_buffer(game, game->player->x, new_y))
        game->player->y = new_y;
}

void move_right(t_game *game)
{
    double new_x;
    double new_y;
    
    new_x = game->player->x + game->player->plane_x * game->player->move_speed;
    new_y = game->player->y + game->player->plane_y * game->player->move_speed;
    
    if (is_valid_position_with_buffer(game, new_x, game->player->y))
        game->player->x = new_x;
    if (is_valid_position_with_buffer(game, game->player->x, new_y))
        game->player->y = new_y;
}

void movment_player(int key, t_game *game)
{
    (void)key;
    
    if (game->mv_forward)
        move_forward(game);
    
    if (game->mv_backward)
        move_backward(game);
    
    if (game->mv_left)
        move_left(game);
    
    if (game->mv_right)
        move_right(game);
    
    if (game->rot_left)
        rotate_player_left(game->player);
    
    if (game->rot_right)
        rotate_player_right(game->player);
}
