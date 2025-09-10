/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/10 18:32:43 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void store_texture(t_data *data, char *line)
{
    if (ft_strncmp(line, "NO", 2) == 0)
        data->path_no = ft_strdup(line + 3);
    else if (ft_strncmp(line, "SO", 2) == 0)
        data->path_so = ft_strdup(line + 3);
    else if (ft_strncmp(line, "WE", 2) == 0)
        data->path_we = ft_strdup(line + 3);
    else if (ft_strncmp(line, "EA", 2) == 0)
        data->path_ea = ft_strdup(line + 3);
}

int is_valid_space(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] == ' ')
            i++;
        else
            break;
    }
    if (i > 2)
        return 1;
    return 0;
}

int parse_texture(char *line)
{
    int result = 0;
    if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
        ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
    {
        if (is_valid_space(line))
            return 0;
        result = 1;
    }
    return result;
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

    line += 2;
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
        printf ("dkhol\n");
        printf("Error\n  Color values must be between 0 and 255\n");
        free_split(rgb_values);
        exit(1);
    }
    color = (r << 16) | (g << 8) | b;
    free_split(rgb_values);
    
    return color;
}

void store_colors(t_data *data, char *line)
{
    if (ft_strncmp(line, "F ", 2) == 0)
        data->floor_color = parse_color(line);
    else if (ft_strncmp(line, "C ", 2) == 0)
        data->ceiling_color = parse_color(line);
    else
    {
        printf("Error\n  Invalid color identifier\n");
        exit(1);
    }
}

void parsing_cub(t_data *data, int fd)
{
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (*line == '\n')
        {
            free(line);
            continue;
        }
        if (parse_texture(line) != 1)
        {
            printf("Error: Invalid texture line\n");
            free(line);
            return ;
        }
        printf("Valid texture line: %s", line);
        store_texture(data, line);
        // store_colors(data, line);
        free(line);
    }
}