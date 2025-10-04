/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:19 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/04 18:11:45 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_data data;
    t_game game;
    ft_bzero(&game, sizeof(t_game));
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
    parsing_cub(&data, fd);
    close(fd);
    game.data = &data;
    /* Ensure player structure is allocated before initializing the game.
       Use malloc + ft_bzero instead of calloc. */
    game.player = (t_player *)malloc(sizeof(t_player));
    if (!game.player)
    {
        printf("Error\n  Memory allocation failed for player\n");
        return 1;
    }
    ft_bzero(game.player, sizeof(t_player));
    init_game(&game);
    /* Note: program exits inside MLX loop; free allocated player on return if needed. */
    return 0;
}
