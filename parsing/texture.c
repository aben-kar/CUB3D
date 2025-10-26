/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:47:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/26 14:57:29 by acben-ka         ###   ########.fr       */
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

static void	check_invalid_config(char **split, t_data *data, t_game *game, char *line)
{
	if (!all_config_parsed(data) && ft_strncmp(split[0], "NO", 3) != 0
		&& ft_strncmp(split[0], "SO", 3) != 0 && ft_strncmp(split[0], "WE",
			3) != 0 && ft_strncmp(split[0], "EA", 3) != 0
		&& ft_strncmp(split[0], "F", 2) != 0 && ft_strncmp(split[0], "C",
			2) != 0)
	{
		while (line)
		{
			free(line);
			line = get_next_line(game->map_fd);
		}
		close(game->map_fd);
		free_split(split);
		print_error_and_exit("Invalid config lineeeee", game);
	}
}

void	parse_config_file(t_data *data, char *line, t_game *game, char *line1)
{
	char	**split;

	if (!line || !line[0])
		return ;
	split = ft_split(line, " ");
	if (!split)
		return ;
	if (!split[0])
	{
		free_split(split);
		return ;
	}
	parse_texture(data, split, game);
	parse_color(data, split, game);
	check_invalid_config(split, data, game, line1);
	free_split(split);
}

void	parse_texture_and_color(t_data *data, int fd, t_game *game)
{
	char	*line;
	char	*cleand;

	game->map_fd = fd;
	line = get_next_line(fd);
	printf("%s", line);
	while (line)
	{	
		if (line[0] == '\n')
		{
			free(line);
			line = get_next_line(fd);
			printf("Empty line found, skipping...\n");
			continue ;
		}
		cleand = ft_strtrim_gc(line, "\n", game);
		
		if (!cleand)
		{
			free(line);
			print_error_and_exit("Memory allocation error", game);
		}
		parse_config_file(data, cleand, game, line);
		free(line);
		if (all_config_parsed(data))
			break ;
		line = get_next_line(fd);
	}
}
