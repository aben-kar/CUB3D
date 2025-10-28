/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:47:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/28 20:21:37 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

char	*build_rgb_string(char **str, t_game *game)
{
	char	*result;
	int		i;

	if (!str || !str[1])
		return (NULL);
	result = ft_strdup_gc("", game);
	if (!result)
		return (NULL);
	i = 1;
	while (str[i])
	{
		result = ft_strjoin_gc(result, str[i], game);
		if (!result)
			return (NULL);
		i++;
	}
	return (result);
}

void	parse_color(t_data *data, char **str, t_game *game)
{
	char	*rgb_string;

	if (!str || !*str)
		return ;
	if (ft_strncmp(str[0], "F", 2) == 0 && str[1])
	{
		if (data->floor_color != 0)
			print_error_and_exit("Duplicate F color", game);
		rgb_string = build_rgb_string(str, game);
		data->floor_color = extract_rgb_color(rgb_string, game);
	}
	else if (ft_strncmp(str[0], "C", 2) == 0 && str[1])
	{
		if (data->ceiling_color != 0)
			print_error_and_exit("Duplicate C color", game);
		rgb_string = build_rgb_string(str, game);
		data->ceiling_color = extract_rgb_color(rgb_string, game);
	}
}

static void	handle_empty_line(char **line, t_game *game)
{
	free(*line);
	game->current_gnl_line = NULL;
	*line = get_next_line(game->map_fd);
}

static void	process_config_line(t_data *data, char *line, t_game *game)
{
	char	*cleand;

	cleand = ft_strtrim_gc(line, "\n", game);
	if (!cleand)
	{
		free(line);
		game->current_gnl_line = NULL;
		get_next_line(-1);
		print_error_and_exit("Memory allocation error", game);
	}
	parse_config_file(data, cleand, game, line);
	free(line);
	game->current_gnl_line = NULL;
}

void	parse_texture_and_color(t_data *data, int fd, t_game *game)
{
	char	*line;

	game->map_fd = fd;
	game->current_gnl_line = NULL;
	line = get_next_line(fd);
	while (line)
	{
		game->current_gnl_line = line;
		if (line[0] == '\n')
		{
			handle_empty_line(&line, game);
			continue ;
		}
		process_config_line(data, line, game);
		if (all_config_parsed(data))
			break ;
		line = get_next_line(fd);
	}
	game->current_gnl_line = NULL;
}
