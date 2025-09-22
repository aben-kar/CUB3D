/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/22 16:37:51 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_map_line(char *line)
{
    int i = 0;

    while (line[i] && line[i] == ' ')
        i++;

    if (!line[i] || line[i] == '\n')
        return 0;

    while (line[i])
    {
        if (line[i] == '\n')
            break;
        if (!ft_strchr("01NSEW ", line[i]))
            return 0;
        i++;
    }
    return 1;
}

void free_split(char **split)
{
    int i = 0;

    if (!split)
        return;

    while (split[i])
    {
        free(split[i]);
        i++;
    }
    free(split);
}

void parse_map_line(t_data *data, char *line)
{
    char *map_line = ft_strdup(line);


    if (!map_line)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    int len = ft_strlen(map_line);
    if (len > 0 && map_line[len - 1] == '\n')
        map_line[len - 1] = '\0';

    int map_size = 0;
    if (data->map)
    {
        while (data->map[map_size])
            map_size++;
    }

    char **new_map = (char **)malloc(sizeof(char *) * (map_size + 2));
    if (!new_map)
    {
        printf("Memory allocation error\n");
        free(map_line);
        exit(1);
    }

    for (int i = 0; i < map_size; i++)
        new_map[i] = data->map[i];
    new_map[map_size] = map_line;
    new_map[map_size + 1] = NULL;

    free(data->map);
    data->map = new_map;
}

void init_data(t_data *data)
{
    data->path_no = NULL;
    data->path_so = NULL;
    data->path_we = NULL;
    data->path_ea = NULL;
    data->floor_color = 0;
    data->ceiling_color = 0;
    data->map = NULL;
}

void parsing_texture_and_color(t_data *data, int fd)
{
    // char *line;
    init_data(data);
    parse_texture_and_color(data, fd);
    

}

// void is_map_valid(t_data *data)
// {
//     // for (int i = 0; data->map[i]; i++)
//     //     printf("%s\n", data->map[i]);
//     replace_espace(data);
// }