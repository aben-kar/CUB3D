/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_config.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/28 21:17:26 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/28 21:17:27 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void	check_invalid_config(
	char **split,
	t_data *data,
	t_game *game,
	char *line)
{
	if (!all_config_parsed(data) && ft_strncmp(split[0], "NO", 3) != 0
		&& ft_strncmp(split[0], "SO", 3) != 0 && ft_strncmp(split[0], "WE",
			3) != 0 && ft_strncmp(split[0], "EA", 3) != 0
		&& ft_strncmp(split[0], "F", 2) != 0 && ft_strncmp(split[0], "C",
			2) != 0)
	{
		game->current_gnl_line = NULL;
		while (line)
		{
			free(line);
			line = get_next_line(game->map_fd);
		}
		close(game->map_fd);
		print_error_and_exit("Invalid config line", game);
	}
}

void	parse_config_file(t_data *data, char *line, t_game *game, char *line1)
{
	char	**split;

	if (!line || !line[0])
		return ;
	split = ft_split_gc(line, " ", game);
	if (!split)
		return ;
	if (!split[0])
		return ;
	parse_texture(data, split, game);
	parse_color(data, split, game);
	check_invalid_config(split, data, game, line1);
}
