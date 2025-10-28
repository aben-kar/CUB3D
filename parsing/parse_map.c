/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:18:43 by achraf            #+#    #+#             */
/*   Updated: 2025/10/27 18:47:56 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (!line[i] || line[i] == '\n')
		return (0);
	while (line[i])
	{
		if (line[i] == '\n')
			break ;
		if (!ft_strchr("01NSEW ", line[i]))
			return (0);
		i++;
	}
	return (1);
}

static char	*skip_empty_lines(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	return (line);
}

char	*map(char *map_joined, char *line, t_game *game)
{
	int		i;
	char	*new_joined;

	check_map_line(map_joined, line, game);
	i = -1;
	while (line[++i])
	{
		if (line[i] == ' ')
			line[i] = '1';
	}
	new_joined = ft_strjoin(map_joined, line);
	if (!new_joined)
	{
		if (map_joined)
			free(map_joined);
		get_next_line(-1);
		print_error_and_exit("Memory allocation error in map join", game);
	}
	if (map_joined)
		free(map_joined);
	return (new_joined);
}

void	parse_map(t_data *data, int fd, t_game *game)
{
	char	*line;
	char	*map_joined;

	map_joined = NULL;
	line = skip_empty_lines(fd);
	while (line)
	{
		check_empty_line_in_map(map_joined, line, game);
		map_joined = map(map_joined, line, game);
		free(line);
		line = get_next_line(fd);
	}
	if (!map_joined)
	{
		get_next_line(-1);
		print_error_and_exit("No valid map found", game);
	}
	data->map = ft_split_gc(map_joined, "\n", game);
	free(map_joined);
	if (!data->map)
	{
		get_next_line(-1);
		print_error_and_exit("Memory allocation error in parse_map", game);
	}
	close(fd);
}
