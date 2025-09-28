/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:29:22 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/28 17:44:28 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char **map_copier(t_data *data)
{
    char **copier_line;
    int line = 0;
    int cols = 0;
    int len;

    while (data->map[line])
    {
        len = ft_strlen(data->map[line]);
        if (len > cols)
            cols = len;
        line++;
    }

    copier_line = (char **)malloc((line + 1) * sizeof(char *));
    if (!copier_line)
        return NULL;

    int i = 0;
    while (i < line)
    {
        int line_lenght = ft_strlen(data->map[i]);

        copier_line[i] = (char *)malloc((cols + 1) * sizeof(char));
        if (!copier_line[i])
            print_error_and_exit("Memory allocation error in map_copier");

        int j = 0;
        while (j < cols)
        {
            if (j < line_lenght)
                copier_line[i][j] = data->map[i][j];
            else
                copier_line[i][j] = '?';
            j++;
        }
        copier_line[i][cols] = '\0';
        i++;
    }
    copier_line[i] = NULL;
    return (copier_line);
}

void is_map_valid(t_data *data)
{
    if (!data->map || !data->map[0])
        print_error_and_exit("Map is empty");
    char **copier_map = map_copier(data);
    is_map_closed(copier_map);
}