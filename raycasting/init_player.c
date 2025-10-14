/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_player.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/02 20:23:04 by aben-kar          #+#    #+#             */
/*   Updated: 2025/10/14 20:05:45 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int key_press(int key, t_game *game)
{
    if (!game || !game->player)
        return (0);
    if (key == KEY_ESC)
        close_window(game);

    if (key == KEY_W) 
        game->mv_forward = 1;
    if (key == KEY_S) 
        game->mv_backward = 1;
    if (key == KEY_A) 
        game->mv_left = 1;
    if (key == KEY_D) 
        game->mv_right = 1;
    if (key == KEY_LEFT) 
        game->rot_left = 1;
    if (key == KEY_RIGHT) 
        game->rot_right = 1;
    return (0);
}


int key_release(int key, t_game *game)
{
    if (!game) return 0;
    if (key == KEY_W) 
        game->mv_forward = 0;
    if (key == KEY_S) 
        game->mv_backward = 0;
    if (key == KEY_A) 
        game->mv_left = 0;
    if (key == KEY_D) 
        game->mv_right = 0;
    if (key == KEY_LEFT) 
        game->rot_left = 0;
    if (key == KEY_RIGHT) 
        game->rot_right = 0;

    return 0;
}
// GUN ANIMATION
int	mouse_press(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1) // Left click
		game->shooting = 1;
	return (0);
}

int	mouse_release(int button, int x, int y, t_game *game)
{
	(void)x;
	(void)y;
	if (button == 1)
		game->shooting = 0;
	return (0);
}
//

int render_frame(t_game *game)
{
    if (!game) return 0;

    if (game->mv_forward)
        movment_player(KEY_W, game);
    if (game->mv_backward)
        movment_player(KEY_S, game);
    if (game->mv_left)
        movment_player(KEY_A, game);
    if (game->mv_right)
        movment_player(KEY_D, game);
    if (game->rot_left)
        movment_player(KEY_LEFT, game);
    if (game->rot_right)
        movment_player(KEY_RIGHT, game);

    game->img = mlx_new_image(game->mlx, SCREEN_WIDTH, SCREEN_HEIGHT);
    game->addr = mlx_get_data_addr(game->img, &game->bits_per_pixel,
                                    &game->line_length, &game->endian);
    raycast_3d(game);
    draw_mini_map(game);
    draw_gun(game);
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
    
    // 4. Destroy image (bach maneb9awch n leak memory)
    mlx_destroy_image(game->mlx, game->img);

    return 0;
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
        game->player->angle = -M_PI / 2.0;
    else if (player_char == 'S')
        game->player->angle = M_PI / 2.0;
    else if (player_char == 'W')
        game->player->angle = M_PI;
    else if (player_char == 'E')
        game->player->angle = 0.0;

    game->player->dir_x = cos(game->player->angle);
    game->player->dir_y = sin(game->player->angle);
    game->player->plane_x = -game->player->dir_y * FOV;
    game->player->plane_y = game->player->dir_x * FOV;
    // TO
    game->player->move_speed = 0.007;
    game->player->rot_speed = 0.003; 
}