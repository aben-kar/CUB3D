/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:17:39 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/30 20:32:54 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
    mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}