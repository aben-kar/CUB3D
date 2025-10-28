/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:19 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/28 17:05:18 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	check_extension_file(const char *filename)
{
	char	*dot;

	dot = ft_strrchr(filename, '.');
	if (!dot || ft_strcmp(dot, ".cub") != 0)
	{
		printf("Error\n  File must have .cub extension\n");
		exit(1);
	}
}

int	open_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
	{
		printf("Error\n  Cannot open file: %s\n", filename);
		exit(1);
	}
	return (fd);
}

int	main(int ac, char **av)
{
	int			fd;
	t_data		data;
	t_player	player;
	t_ray		ray;
	t_game		game;

	data = (t_data){0};
	player = (t_player){0};
	ray = (t_ray){0};
	game = (t_game){0};
	game.gc = NULL;
	if (ac != 2)
	{
		printf("Error\n  Usage: ./cub3d <map.cub>\n");
		return (1);
	}
	check_extension_file(av[1]);
	fd = open_file(av[1]);
	parsing_cub(&data, fd, &game);
	game.data = &data;
	game.player = &player;
	game.ray = &ray;
	init_game(&game);
	close_window(&game);
}
