/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_map_gun.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:17:39 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/16 12:30:00 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int close_window(t_game *game)
{
	destroy_textures(game);

	mlx_destroy_window(game->mlx, game->mlx_win);
	mlx_destroy_display(game->mlx);
	free(game->mlx);
	exit(0);
    return 0;
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
    int cell_size = 5; // Size dyal kol cell f mini-map
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

void    draw_gun(t_game *game)
{
	t_texture *gun;
	int gx, gy;
	int color;
	int start_x;
	int start_y;

	// choose gun texture
	if (game->shooting)
		gun = &game->gun_fire;
	else
		gun = &game->gun_idle;

	if (!gun || !gun->img || !gun->addr)
		return;

	// bottom-center position (no scaling)
	start_x = (SCREEN_WIDTH / 2) - (gun->width / 2);
	start_y = SCREEN_HEIGHT - gun->height;

	// draw gun pixel by pixel
	gy = 0;
	while (gy < gun->height)
	{
		gx = 0;
		while (gx < gun->width)
		{
			color = get_tex_pixel_color(gun, gx, gy);
			// skip transparent pixels (black = transparent)
			if ((color & 0x00FFFFFF) != 0x000000)
				my_mlx_pixel_put(game, start_x + gx, start_y + gy, color);
			gx++;
		}
		gy++;
	}
}
