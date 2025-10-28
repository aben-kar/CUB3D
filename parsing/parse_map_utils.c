/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 18:31:54 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/28 16:08:04 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_map_line(char *map_joined, char *line, t_game *game)
{
	if (!line)
		return ;
	if (!is_map_line(line))
	{
		free(line);
		if (map_joined)
			free(map_joined);
		get_next_line(-1);
		print_error_and_exit("Invalid map line", game);
	}
}

void	check_empty_line_in_map(char *map_joined, char *line, t_game *game)
{
	if (!line)
		return ;
	if (line[0] == '\n')
	{
		free(line);
		if (map_joined)
			free(map_joined);
		get_next_line(-1);
		print_error_and_exit("Empty line found inside the map", game);
	}
}
