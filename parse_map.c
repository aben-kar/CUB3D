/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:18:43 by achraf            #+#    #+#             */
/*   Updated: 2025/09/28 17:41:16 by acben-ka         ###   ########.fr       */
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

static char *skip_empty_lines(int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line && line[0] == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}

// void free_map(t_data *data)
// {
//     int i = 0;

//     if (!data->map)
//         return;
//     while (data->map[i])
//     {
//         free(data->map[i]);
//         i++;
//     }
//     free(data->map);
//     data->map = NULL;
// }

char *map(char *map_joined, char *line)
{
    int i = 0;
    char *tmp;
    if (!is_map_line(line))
    {
        free(line);
        free(map_joined);
        print_error_and_exit("Invalid map line");
    }
    while (line[i])
    {
        if (line[i] == ' ')
            line[i] = '1';
        i++;
    }
    tmp = map_joined;
    map_joined = ft_strjoin(map_joined, line);
    free(tmp);
    return (map_joined);
}

void parse_map(t_data *data, int fd)
{
    char *line;
    char *map_joined;

    map_joined = NULL;
    line = skip_empty_lines(fd);
    while (line)
    {
        if (line[0] == '\n')
        {
            free(line);
            free(map_joined);
            print_error_and_exit("Empty line found inside the map");
        }
        map_joined = map(map_joined, line);
        free(line);
        line = get_next_line(fd);
    }
    data->map = ft_split(map_joined, '\n');
    if (!data->map)
        print_error_and_exit("Memory allocation error in parse_map");
    free(map_joined);
}
