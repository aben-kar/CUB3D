/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:19 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/29 18:04:20 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_data data;
    t_game game;
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
    init_game(&game);
    
    return 0;
}
