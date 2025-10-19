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

static int	get_max_cols(char **map)
{
	int	i;
	int	max;

	i = 0;
	max = 0;
	while (map[i])
	{
		if ((int)ft_strlen(map[i]) > max)
			max = ft_strlen(map[i]);
		i++;
	}
	return (max);
}

static void	alloc_rows(char **dst, t_mapinfo info, t_game *game)
{
	int	i;

	i = 0;
	while (i < info.lines)
	{
		dst[i] = gc_alloc((info.cols + 1) * sizeof(char), game);
		if (!dst[i])
			print_error_and_exit("Memory allocation error in map_copier", game);
		copy_map_row(dst[i], info.src[i], info.cols);
		i++;
	}
	dst[i] = NULL;
}

char	**map_copier(t_data *data, t_game *game)
{
	char		**copy;
	t_mapinfo	info;

	info.lines = 0;
	while (data->map[info.lines])
		info.lines++;
	info.cols = get_max_cols(data->map);
	info.src = data->map;
	copy = gc_alloc((info.lines + 1) * sizeof(char *), game);
	if (!copy)
		return (NULL);
	alloc_rows(copy, info, game);
	return (copy);
}

void	is_map_valid(t_data *data, t_game *game)
{
	char	**copier_map;

	if (!data->map || !data->map[0])
		print_error_and_exit("Map is empty", game);
	copier_map = map_copier(data, game);
	is_map_closed(copier_map, game);
}
