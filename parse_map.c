/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:18:43 by achraf            #+#    #+#             */
/*   Updated: 2025/09/25 22:53:23 by acben-ka         ###   ########.fr       */
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

void parse_map_line(t_data *data, char *line)
{
    char *map_line = ft_strdup(line);

    if (!map_line)
        print_error_and_exit("Memory allocation error\n");

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

void free_map(t_data *data)
{
    int i = 0;

    if (!data->map)
        return;
    while (data->map[i])
    {
        free(data->map[i]);
        i++;
    }
    free(data->map);
    data->map = NULL;
}

void map(t_data *data, char *line)
{
    int i = 0;

    if (!is_map_line(line))
    {
        free(line);
        print_error_and_exit("Invalid map line");
    }
    while (line[i])
    {
        // replace espace
        if (line[i] == ' ')
            line[i] = '1';
        i++;
    }
    parse_map_line(data, line);
}

static char *skip_empty_lines(int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line[0] == '\n')
    {
        free(line);
        line = get_next_line(fd);
    }
    return (line);
}

void parse_map(t_data *data, int fd)
{
    char *line;

    line = skip_empty_lines(fd);
    while (line)
    {
        if (!line)
        {
            print_error_and_exit("Empty line found inside the map");
        }
        if (line[0] == '\n')
        {
            free(line);
            free_map(data);
            print_error_and_exit("Empty line found inside the map");
        }
        map(data, line);
        free(line);
        line = get_next_line(fd);
    }
    free(line);
}

char **map_copier(t_data *data)
{
    char **copier_line;
    int line = 0;

    while (data->map[line])
        line++;
    
    copier_line = (char **)malloc((line + 1) * sizeof(char *));
    if (!copier_line)
        return NULL;
    
    int i = 0;
    while (data->map[i])
    {
        copier_line[i] = ft_strdup(data->map[i]);
        if (!copier_line[i])
            print_error_and_exit("Memory allocation error in map_copier");
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
    validation_map(copier_map);
}