/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aben-kar <aben-kar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:17:39 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/02 18:19:18 by aben-kar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <math.h>

int render_frame(t_game *game)
{
    // Clear screen
    ft_memset(game->addr, 0, SCREEN_WIDTH * SCREEN_HEIGHT * (game->bits_per_pixel / 8));
    
    // Redessiner tout
    draw_mini_map(game);
    
    return (0);
}

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

int key_press(int key, t_game *game)
{
    if (!game || !game->player)
        return (0);
    double new_x = game->player->x;
    double new_y = game->player->y;
    double move_speed = game->player->move_speed;

    if (key == 65307) // ESC key
        close_window(game);
    if (key == KEY_W)
    {
        new_x = game->player->x + game->player->dir_x * move_speed;
        new_y = game->player->y + game->player->dir_y * move_speed;
    }
    if (key == KEY_S)
    {
        new_x = game->player->x - game->player->dir_x * move_speed;
        new_y = game->player->y - game->player->dir_y * move_speed;
    }
    if (key == KEY_A)
    {
        new_x = game->player->x - game->player->plane_y * move_speed;
        new_y = game->player->y + game->player->plane_x * move_speed;
    }
    if (key == KEY_D)
    {
        new_x = game->player->x + game->player->plane_y * move_speed;
        new_y = game->player->y - game->player->plane_x * move_speed;
    }
    if (key == KEY_LEFT)  // Flèche gauche
        rotate_player_left(game->player);
    if (key == KEY_RIGHT) // Flèche droite
        rotate_player_right(game->player);

    // Vérifier collision avant de mettre à jour
    if (!is_wall(game, new_x, new_y))
    {
        game->player->x = new_x;
        game->player->y = new_y;
    }
    draw_mini_map(game);
    
    return (0);
}

int close_window(t_game *game)
{
    mlx_destroy_window(game->mlx, game->mlx_win);
    exit(0);
    return (0);
}

void init_player(t_game *game)
{
    int i, j;
    char player_char = 0;
    
    // Allocate memory lel player
    game->player = malloc(sizeof(t_player));
    if (!game->player)
    {
        printf("Error\nFailed to allocate player memory\n");
        exit(1);
    }
    
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
                break;
            }
        }
        if (player_char)
            break;
    }
    
    if (player_char == 'N')
        game->player->angle = -M_PI / 2.0;
    else if (player_char == 'S')
        game->player->angle = M_PI / 2.0;
    else if (player_char == 'W')
        game->player->angle = M_PI;
    else if (player_char == 'E')
        game->player->angle = 0.0;

    game->dir_x = cos(game->player->angle);
    game->dir_y = sin(game->player->angle);
    game->player->move_speed = 0.05;
    game->player->rot_speed = 0.03;
}

void my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
    char *dst;

    dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
    *(unsigned int *)dst = color;
}

void draw_rectangle(t_game *game, int x, int y, int cell_size, int color)
{
    int i, j;
    for (i = 0; i < cell_size; i++)
    {
        for (j = 0; j < cell_size; j++)
        {
            my_mlx_pixel_put(game, x + j, y + i, color);
        }
    }
}

void draw_mini_map(t_game *game)
{
    if (!game || !game->data || !game->data->map)
    {
        print_error_and_exit("Game is NULL");
        return;
    }
    int map_rows = 0;
    while (game->data->map[map_rows])
        map_rows++;
    game->map_rows = map_rows;
    int cell_size = 5; // Size dyal kol cell f mini-map and bach converti position dyal player l pixels
    int i, j;
    int color;

    for (i = 0; i < game->map_rows; i++)
    {
        int row_len = ft_strlen(game->data->map[i]);
        for (j = 0; j < row_len; j++)
        {
            if (game->data->map[i][j] == '1')
                color = 0x888888; // gray for wall
            else if (game->data->map[i][j] == '0')
                color = 0xFFFFFF; // white for space
            else if (game->data->map[i][j] == 'N' || game->data->map[i][j] == 'S' ||
                     game->data->map[i][j] == 'E' || game->data->map[i][j] == 'W')
                color = 0xFF0000; // red for player
            draw_rectangle(game, j * cell_size, i * cell_size, cell_size, color);
        }
    }
    
    if (game->player)
    {
        int player_x = (int)(game->player->x * cell_size);
        int player_y = (int)(game->player->y * cell_size);
        draw_rectangle(game, player_x - 2, player_y - 2, 4, 0xFF0000);
    }
    
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}