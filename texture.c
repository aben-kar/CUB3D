/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:47:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/22 19:00:29 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#include <stdio.h>
#include <stdlib.h>

void print_error_and_exit(const char *msg)
{
    printf("Error\n%s\n", msg);
    exit(1);
}

int all_config_parsed(t_data *data)
{
    return (data->path_no && data->path_so &&
            data->path_we && data->path_ea &&
            data->floor_color != 0 && data->ceiling_color != 0);
}

void parse_texture(t_data *data, char **str)
{
    if (ft_strncmp(str[0], "NO", 3) == 0 && str[1] && !str[2])
        data->path_no = ft_strdup(str[1]);
    else if (ft_strncmp(str[0], "SO", 3) == 0 && str[1] && !str[2])
        data->path_so = ft_strdup(str[1]);
    else if (ft_strncmp(str[0], "WE", 3) == 0 && str[1] && !str[2])
        data->path_we = ft_strdup(str[1]);
    else if (ft_strncmp(str[0], "EA", 3) == 0 && str[1] && !str[2])
        data->path_ea = ft_strdup(str[1]);
}

void parse_color(t_data *data, char **str)
{
    if (ft_strncmp(str[0], "F", 2) == 0 && str[1] && !str[2])
        data->floor_color = extract_rgb_color(str[1]);

    else if (ft_strncmp(str[0], "C", 2) == 0 && str[1] && !str[2])
        data->ceiling_color = extract_rgb_color(str[1]);
}

void parse_config_file(t_data *data, char *line)
{
    char **split;

    split = ft_split(line, ' ');
    if (!split || !split[0])
    {
        free_split(split);
        return;
    }
    parse_texture(data, split);
    parse_color(data, split);
    
    if (!all_config_parsed(data) &&
        ft_strncmp(split[0], "NO", 3) != 0 &&
        ft_strncmp(split[0], "SO", 3) != 0 &&
        ft_strncmp(split[0], "WE", 3) != 0 &&
        ft_strncmp(split[0], "EA", 3) != 0 &&
        ft_strncmp(split[0], "F", 2) != 0 &&
        ft_strncmp(split[0], "C", 2) != 0)
    {
        free_split(split);
        print_error_and_exit("Invalid config line");
    }
    free_split(split);
}

void parse_texture_and_color(t_data *data, int fd)
{
    char *line;

    line = get_next_line(fd);
    while (line)
    {
        // skip empty lines
        if (line[0] == '\n')
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }

        parse_config_file(data, line);
        // free(line);
        line = get_next_line(fd);
    }
    free(line);
}