/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zaakrab <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:46:19 by zaakrab           #+#    #+#             */
/*   Updated: 2025/10/18 20:46:21 by zaakrab          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

bool	is_player(char position)
{
	return (position == 'N' || position == 'S' || position == 'W'
		|| position == 'E');
}

void	parse_texture(t_data *data, char **str, t_game *game)
{
	if (!str || !*str)
		return ;
	if (ft_strncmp(str[0], "NO", 3) == 0 && str[1] && !str[2])
	{
		if (data->path_no)
			print_error_and_exit("Duplicate NO texture", game);
		data->path_no = ft_strdup_gc(str[1], game);
	}
	else if (ft_strncmp(str[0], "SO", 3) == 0 && str[1] && !str[2])
	{
		if (data->path_so)
			print_error_and_exit("Duplicate SO texture", game);
		data->path_so = ft_strdup_gc(str[1], game);
	}
	else if (ft_strncmp(str[0], "WE", 3) == 0 && str[1] && !str[2])
	{
		if (data->path_we)
			print_error_and_exit("Duplicate WE texture", game);
		data->path_we = ft_strdup_gc(str[1], game);
	}
	else if (ft_strncmp(str[0], "EA", 3) == 0 && str[1] && !str[2])
	{
		if (data->path_ea)
			print_error_and_exit("Duplicate EA texture", game);
		data->path_ea = ft_strdup_gc(str[1], game);
	}
}

void	check_multiple_player(t_data *data, t_game *game)
{
	int	i;
	int	j;
	int	player;

	if (!data->map || !data->map[0])
		return ;
	i = 0;
	player = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
				data->map[i][j] == 'E' || data->map[i][j] == 'W')
				player++;
			j++;
		}
		i++;
	}
	if (player > 1)
		print_error_and_exit("The map must contain one player only",
			game);
}
