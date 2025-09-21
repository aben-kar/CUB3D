/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/21 23:19:20 by achraf           ###   ########.fr       */
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

int parse_color(char *line)
{
    char **rgb_values;
    int r, g, b;
    int color;

    rgb_values = ft_split(line, ',');
    if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3])
    {
        printf("Error\n  Invalid color format\n");
        free_split(rgb_values);
        exit(1);
    }

    r = ft_atoi(rgb_values[0]);
    g = ft_atoi(rgb_values[1]);
    b = ft_atoi(rgb_values[2]);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        printf("Error\n  Color values must be between 0 and 255\n");
        free_split(rgb_values);
        exit(1);
    }
    color = (r << 16) | (g << 8) | b;
    free_split(rgb_values);

    return color;
}

int parse_config_file(t_data *data, char *line)
{
    // printf("line ==> %s", line);
    if (ft_strncmp(line, "NO ", 3) == 0)
    {
        data->path_no = ft_strtrim(line + 3, " \n");
        return 1;
    }
    else if (ft_strncmp(line, "SO ", 3) == 0)
    {
        data->path_so = ft_strtrim(line + 3, " \n");
        return 1;
    }
    else if (ft_strncmp(line, "WE ", 3) == 0)
    {
        data->path_we = ft_strtrim(line + 3, " \n");
        return 1;
    }
    else if (ft_strncmp(line, "EA ", 3) == 0)
    {
        data->path_ea = ft_strtrim(line + 3, " \n");
        return 1;
    }
    else if (ft_strncmp(line, "F ", 2) == 0)
    {
        data->floor_color = parse_color(line + 2);
        return 1;
    }
    else if (ft_strncmp(line, "C ", 2) == 0)
    {
        data->ceiling_color = parse_color(line + 2);
        return 1;
    }
    return 0;
}

int all_config_parsed(t_data *data)
{
    return (data->path_no && data->path_so &&
            data->path_we && data->path_ea &&
            data->floor_color != 0 && data->ceiling_color != 0);
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

void parsing_texture_and_color(t_data *data, int fd)
{
    char *line;
    int config_phase = 1; // 1 = parsing config, 0 = parsing map

    data->path_no = NULL;
    data->path_so = NULL;
    data->path_we = NULL;
    data->path_ea = NULL;
    data->floor_color = 0;
    data->ceiling_color = 0;
    data->map = NULL;

    while ((line = get_next_line(fd)) != NULL)
    {
        int only_spaces = 1;
        for (int i = 0; line[i]; i++)
        {
            if (line[i] != '\n')
            {
                only_spaces = 0;
                break;
            }
        }

        if (only_spaces && config_phase)
        {
            free(line);
            continue;
        }
        else if (only_spaces && !config_phase)
            continue;

        if (config_phase)
        {
            if (parse_config_file(data, line))
            {
                if (all_config_parsed(data))
                    config_phase = 0;
            }
            else if (is_map_line(line))
                config_phase = 0;
            else
            {
                printf("ERROR: Invalid config line: %s", line);
                free(line);
                exit(1);
            }
        }
        else
        {
            
            if (is_map_line(line))
                parse_map_line(data, line);
            else
            {
                printf("ERROR: Invalid map line: %s", line);
                free(line);
                exit(1);
            }
        }
        free(line);
    }
}

void is_map_valid(t_data *data)
{
    // for (int i = 0; data->map[i]; i++)
    //     printf("%s\n", data->map[i]);
    check_multiple_players(data);
    
}