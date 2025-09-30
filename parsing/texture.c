/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:47:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/29 17:43:10 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
    if (!str || !*str)
        return;
    if (ft_strncmp(str[0], "NO", 3) == 0 && str[1] && !str[2])
    {
        if (data->path_no)
            print_error_and_exit("Duplicate NO texture");
        data->path_no = ft_strdup(str[1]);
    }
    else if (ft_strncmp(str[0], "SO", 3) == 0 && str[1] && !str[2])
    {
        if (data->path_so)
            print_error_and_exit("Duplicate SO texture");
        data->path_so = ft_strdup(str[1]);
    }
    else if (ft_strncmp(str[0], "WE", 3) == 0 && str[1] && !str[2])
    {
        if (data->path_we)
            print_error_and_exit("Duplicate WE texture");
        data->path_we = ft_strdup(str[1]);
    }
    else if (ft_strncmp(str[0], "EA", 3) == 0 && str[1] && !str[2])
    {
        if (data->path_ea)
            print_error_and_exit("Duplicate EA texture");
        data->path_ea = ft_strdup(str[1]);
    }
}

void parse_color(t_data *data, char **str)
{
    if (!str || !*str)
        return;
    
    if (ft_strncmp(str[0], "F", 2) == 0 && str[1] && !str[2])
    {
        if (data->floor_color != 0)
            print_error_and_exit("Duplicate F color");
        data->floor_color = extract_rgb_color(str[1]);
    }
    else if (ft_strncmp(str[0], "C", 2) == 0 && str[1] && !str[2])
    {
        if (data->ceiling_color != 0)
            print_error_and_exit("Duplicate C color");
        data->ceiling_color = extract_rgb_color(str[1]);
    }
}

void parse_config_file(t_data *data, char *line)
{
    if (!line || !line[0])
        return;
    
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
    char *cleand;

    line = get_next_line(fd);
    while (line)
    {
        if (line[0] == '\n')
        {
            free(line);
            line = get_next_line(fd);
            continue;
        }
        cleand = ft_strtrim(line, "\n");
        parse_config_file(data, cleand);
        if (all_config_parsed(data))
        {
            free(cleand);
            break;
        }
        free(line);
        line = get_next_line(fd);
    }
    free(line);
}
