/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/28 15:48:01 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	print_error_and_exit(const char *msg, t_game *game)
{
	printf("Error\n   %s\n", msg);
	cleanup_and_exit(game, 1);
}

int	all_config_parsed(t_data *data)
{
	return (data->path_no && data->path_so && data->path_we && data->path_ea
		&& data->floor_color != 0 && data->ceiling_color != 0);
}

void	init_data(t_data *data)
{
	data->path_no = NULL;
	data->path_so = NULL;
	data->path_we = NULL;
	data->path_ea = NULL;
	data->floor_color = 0;
	data->ceiling_color = 0;
	data->map = NULL;
}

void	parsing_cub(t_data *data, int fd, t_game *game)
{
	init_data(data);
	parse_texture_and_color(data, fd, game);
	parse_map(data, fd, game);
	is_map_valid(data, game);
}
