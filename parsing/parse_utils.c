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

static void	set_texture(char **str, char **path, char *name, t_game *game)
{
	(void)name;
	if (*path)
		print_error_and_exit("Duplicate texture", game);
	*path = ft_strdup_gc(str[1], game);
}

void	parse_texture(t_data *data, char **str, t_game *game)
{
	if (!str || !*str)
		return ;
	if (ft_strncmp(str[0], "NO", 3) == 0 && str[1] && !str[2])
		set_texture(str, &data->path_no, "NO", game);
	else if (ft_strncmp(str[0], "SO", 3) == 0 && str[1] && !str[2])
		set_texture(str, &data->path_so, "SO", game);
	else if (ft_strncmp(str[0], "WE", 3) == 0 && str[1] && !str[2])
		set_texture(str, &data->path_we, "WE", game);
	else if (ft_strncmp(str[0], "EA", 3) == 0 && str[1] && !str[2])
		set_texture(str, &data->path_ea, "EA", game);
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
