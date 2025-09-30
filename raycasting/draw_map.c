/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:17:39 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/30 22:41:40 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"


int key_press(int keycode, t_game *game)
{
    if (keycode == 65307) // ESC key
    {
        mlx_destroy_window(game->mlx, game->mlx_win);
        exit(0);
    }
    if (keycode == 119 || keycode == 65362) // W key ola UP arrow
    {
        // Move forward
        double new_x = game->player->x + game->player->dir_x * game->player->move_speed;
        double new_y = game->player->y + game->player->dir_y * game->player->move_speed;
        
        // Check collision m3a walls
        if (game->data->map[(int)new_y][(int)new_x] != '1')
        {
            game->player->x = new_x;
            game->player->y = new_y;
        }
    }
    if (keycode == 115 || keycode == 65364) // S key ola DOWN arrow
    {
        // Move backward
        double new_x = game->player->x - game->player->dir_x * game->player->move_speed;
        double new_y = game->player->y - game->player->dir_y * game->player->move_speed;
        
        if (game->data->map[(int)new_y][(int)new_x] != '1')
        {
            game->player->x = new_x;
            game->player->y = new_y;
        }
    }
    if (keycode == 97 || keycode == 65361) // A key ola LEFT arrow
    {
        // Rotate left
        double old_dir_x = game->player->dir_x;
        game->player->dir_x = game->player->dir_x * cos(game->player->rot_speed) - game->player->dir_y * sin(game->player->rot_speed);
        game->player->dir_y = old_dir_x * sin(game->player->rot_speed) + game->player->dir_y * cos(game->player->rot_speed);
        
        double old_plane_x = game->player->plane_x;
        game->player->plane_x = game->player->plane_x * cos(game->player->rot_speed) - game->player->plane_y * sin(game->player->rot_speed);
        game->player->plane_y = old_plane_x * sin(game->player->rot_speed) + game->player->plane_y * cos(game->player->rot_speed);
    }
    if (keycode == 100 || keycode == 65363) // D key ola RIGHT arrow
    {
        // Rotate right
        double old_dir_x = game->player->dir_x;
        game->player->dir_x = game->player->dir_x * cos(-game->player->rot_speed) - game->player->dir_y * sin(-game->player->rot_speed);
        game->player->dir_y = old_dir_x * sin(-game->player->rot_speed) + game->player->dir_y * cos(-game->player->rot_speed);
        
        double old_plane_x = game->player->plane_x;
        game->player->plane_x = game->player->plane_x * cos(-game->player->rot_speed) - game->player->plane_y * sin(-game->player->rot_speed);
        game->player->plane_y = old_plane_x * sin(-game->player->rot_speed) + game->player->plane_y * cos(-game->player->rot_speed);
    }
    
    // Redraw la scene ba3d kol movement
    mlx_clear_window(game->mlx, game->mlx_win);
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
        // if (player_char)
        //     break;
    }
    printf ("Player position: (%.2f, %.2f)\n", game->player->x, game->player->y);
    
    // Set direction hasab orientation
    if (player_char == 'N')
    {
        game->player->dir_x = 0;
        game->player->dir_y = -1;
        game->player->plane_x = 0.66; // FOV
        game->player->plane_y = 0;
    }
    else if (player_char == 'S')
    {
        game->player->dir_x = 0;
        game->player->dir_y = 1;
        game->player->plane_x = -0.66;
        game->player->plane_y = 0;
    }
    else if (player_char == 'E')
    {
        game->player->dir_x = 1;
        game->player->dir_y = 0;
        game->player->plane_x = 0;
        game->player->plane_y = 0.66;
    }
    else if (player_char == 'W')
    {
        game->player->dir_x = -1;
        game->player->dir_y = 0;
        game->player->plane_x = 0;
        game->player->plane_y = -0.66;
    }
    
    // Set movement speeds
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
    int cell_size = 5;
    int i, j;
    int color;

    for (i = 0; i < map_rows; i++)
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
    
    printf ("Player position: (%.2f, %.2f)\n", game->player->x, game->player->y);

    if (game->player)
    {
        int player_x = (int)(game->player->x * cell_size);
        int player_y = (int)(game->player->y * cell_size);
        draw_rectangle(game, player_x - 2, player_y - 2, 4, 0xFF0000); // red circle sghir
    }
    
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}