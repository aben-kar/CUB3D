/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:29:22 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/16 12:29:53 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

static void	copy_map_row(char *dest, char *src, int cols)
{
	int	j;
	int	len;

	len = ft_strlen(src);
	j = 0;
	while (j < cols)
	{
		if (j < len)
			dest[j] = src[j];
		else
			dest[j] = '?';
		j++;
	}
	dest[cols] = '\0';
}

char	**map_copier(t_data *data, t_game *game)
{
	char	**copier_line;
	int		line;
	int		cols;
	int		i;

	line = 0;
	cols = 0;
	while (data->map[line])
	{
		if ((int)ft_strlen(data->map[line]) > cols)
			cols = ft_strlen(data->map[line]);
		line++;
	}
	copier_line = (char **)gc_alloc((line + 1) * sizeof(char *), game);
	if (!copier_line)
		return (NULL);
	i = 0;
	while (i < line)
	{
		copier_line[i] = (char *)gc_alloc((cols + 1) * sizeof(char), game);
		if (!copier_line[i])
			print_error_and_exit("Memory allocation error in map_copier", game);
		copy_map_row(copier_line[i], data->map[i], cols);
		i++;
	}
	copier_line[i] = NULL;
	return (copier_line);
}

void	is_map_valid(t_data *data, t_game *game)
{
	char	**copier_map;

	if (!data->map || !data->map[0])
		print_error_and_exit("Map is empty", game);
	copier_map = map_copier(data, game);
	is_map_closed(copier_map, game);
}
