/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movment_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 17:48:21 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/20 15:29:37 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_valid_position(t_game *game, double x, double y)
{
	int	map_x;
	int	map_y;

	map_x = (int)x;
	map_y = (int)y;
	if (map_x < 0 || map_y < 0)
		return (0);
	if (map_y >= game->map_rows)
		return (0);
	if (map_x >= (int)ft_strlen(game->data->map[map_y]))
		return (0);
	if (game->data->map[map_y][map_x] == '1')
		return (0);
	return (1);
}

int	is_valid_position_with_buffer(t_game *game, double x, double y)
{
	double	buffer;

	buffer = 0.2;
	if (!is_valid_position(game, x - buffer, y - buffer))
		return (0);
	if (!is_valid_position(game, x + buffer, y - buffer))
		return (0);
	if (!is_valid_position(game, x - buffer, y + buffer))
		return (0);
	if (!is_valid_position(game, x + buffer, y + buffer))
		return (0);
	return (1);
}
