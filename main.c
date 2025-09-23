/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:19 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/23 22:52:38 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int main(int ac, char **av)
{
    t_data data;
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

    parsing_texture_and_color(&data, fd);
    // printf ("no ==> %s\n", data.path_no);
    // printf ("so ==> %s\n", data.path_so);
    // printf ("we ==> %s\n", data.path_we);
    // printf ("ea ==> %s\n", data.path_ea);
    // printf ("f ==> %d\n", data.floor_color);
    // printf ("c ==> %d\n", data.ceiling_color);
    // // print map
    // int i = 0;
    // while (data.map[i])
    // {
    //     printf("map line %d: %s\n", i, data.map[i]);
    //     i++;
    // }
    close(fd);
    return 0;
}