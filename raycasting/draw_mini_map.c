/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini_map.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/30 17:17:39 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/20 16:28:30 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	my_mlx_pixel_put(t_game *game, int x, int y, int color)
{
	char	*dst;

	dst = game->addr + (y * game->line_length + x * (game->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	draw_rectangle(t_game *game, int x, int y, int cell_size)
{
	int	i;
	int	j;

	i = 0;
	while (i < cell_size)
	{
		j = 0;
		while (j < cell_size)
		{
			my_mlx_pixel_put(game, x + j, y + i, game->draw_color);
			j++;
		}
		i++;
	}
}

int	count_rows(t_game *game)
{
	int	i;

	i = 0;
	while (game->data->map[i])
		i++;
	return (i);
}

void	init_map(t_game *game, int cell_size)
{
	int	i;
	int	j;
	int	row_len;

	game->map_rows = count_rows(game);
	i = -1;
	while (++i < game->map_rows)
	{
		j = 0;
		row_len = ft_strlen(game->data->map[i]);
		while (j < row_len)
		{
			if (game->data->map[i][j] == '1')
				game->draw_color = 0x888888;
			else if (game->data->map[i][j] == '0')
				game->draw_color = 0xFFFFFF;
			else if (game->data->map[i][j] == 'N'
					|| game->data->map[i][j] == 'S'
					|| game->data->map[i][j] == 'E'
					|| game->data->map[i][j] == 'W')
				game->draw_color = 0xFF0000;
			draw_rectangle(game, j * cell_size, i * cell_size, cell_size);
			j++;
		}
	}
}

void	draw_mini_map(t_game *game)
{
	int	cell_size;
	int	player_x;
	int	player_y;

	if (!game || !game->data || !game->data->map)
		print_error_and_exit("Game is NULL", game);
	cell_size = 5;
	init_map(game, cell_size);
	if (game->player)
	{
		player_x = (int)(game->player->x * cell_size);
		player_y = (int)(game->player->y * cell_size);
		game->draw_color = 0xFF0000;
		draw_rectangle(game, player_x - 2, player_y - 2, 4);
	}
	mlx_put_image_to_window(game->mlx, game->mlx_win, game->img, 0, 0);
}
