/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:45:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/16 12:29:49 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	check_row_top(char **map, t_game *game)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] != '1' && map[0][i] != '?')
			print_error_and_exit("Map not closed", game);
		if (map[0][i] == '?' && map[1][i] && map[1][i] != '1'
			&& map[1][i] != '?')
			print_error_and_exit("Map not closed", game);
		i++;
	}
}

static void	check_row_bottom(char **map, int rows, t_game *game)
{
	int	i;

	i = 0;
	while (map[rows - 1][i])
	{
		if (map[rows - 1][i] != '1' && map[rows - 1][i] != '?')
			print_error_and_exit("Map not closed", game);
		if (map[rows - 1][i] == '?' && map[rows - 2][i] && map[rows
			- 2][i] != '1' && map[rows - 2][i] != '?')
			print_error_and_exit("Map not closed", game);
		i++;
	}
}

static void	check_row_sides(char **map, int i, t_game *game)
{
	int	k;
	int	len;

	k = 0;
	len = ft_strlen(map[i]);
	while (map[i][k])
	{
		if (map[i][k] == '?')
		{
			if (k - 1 >= 0 && map[i][k - 1] != '1' && map[i][k - 1] != '?')
				print_error_and_exit("Map not closed", game);
			if (i - 1 >= 0 && map[i - 1][k] && map[i - 1][k] != '1' && map[i
				- 1][k] != '?')
				print_error_and_exit("Map not closed", game);
		}
		k++;
	}
	if (map[i][0] != '1' && map[i][0] != '?')
		print_error_and_exit("Map not closed", game);
	if (map[i][len - 1] != '1' && map[i][len - 1] != '?')
		print_error_and_exit("Map not closed", game);
}

static int	count_players(char **map)
{
	int	i;
	int	j;
	int	player;

	player = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_player(map[i][j]))
				player++;
			j++;
		}
		i++;
	}
	return (player);
}

void	is_map_closed(char **map, t_game *game)
{
	int	i;
	int	rows;

	if (!map || !map[0])
		return ;
	rows = 0;
	while (map[rows])
		rows++;
	check_row_top(map, game);
	check_row_bottom(map, rows, game);
	i = 0;
	while (i < rows)
	{
		check_row_sides(map, i, game);
		i++;
	}
	if (count_players(map) != 1)
		print_error_and_exit("The map must contain one player", game);
}
