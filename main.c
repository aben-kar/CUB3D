/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:19 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/25 22:01:02 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int main(int ac, char **av)
{
    t_data data = {0};
    t_player player = {0};
    t_ray ray = {0};
    t_game game = {0};
    
    game.gc = NULL;
    if (ac != 2)
    {
        printf("Error\n  Usage: ./cub3d <map.cub>\n");
        return 1;
    }

    if (!ft_strchr(av[1], '.') || ft_strcmp(ft_strrchr(av[1], '.'), ".cub") != 0)
    {
        printf("Error\n  File must have .cub extension\n");
        return 1;
    }

    int fd = open(av[1], O_RDONLY);
    if (fd < 0)
    {
        printf("Error\n  Cannot open file: %s\n", av[1]);
        return 1;
    }
    parsing_cub(&data, fd, &game);
    game.data = &data;
    game.player = &player;
    game.ray = &ray;
    init_game(&game);
    close_window(&game);
}
