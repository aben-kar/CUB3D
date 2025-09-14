/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/14 16:31:23 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char *parse_texture(char *line)
{
    char *path;

    path = ft_strtrim(line + 3, " \n");
    if (!path || *path == '\0') // Check if path is empty or invalid
    {
        printf("Error\n  Invalid texture path: %s\n", line);
        free(path);
        return NULL;
    }
    return path; // Return the valid path
}

int store_texture(t_data *data, char *line)
{
    if (ft_strncmp(line, "NO ", 3) == 0)
        data->path_no = parse_texture(line);
    else if (ft_strncmp(line, "SO ", 3) == 0)
        data->path_so = parse_texture(line);
    else if (ft_strncmp(line, "WE ", 3) == 0)
        data->path_we = parse_texture(line);
    else if (ft_strncmp(line, "EA ", 3) == 0)
        data->path_ea = parse_texture(line);
    else
    {
        printf("Error\n  Invalid texture line: %s\n", line); // Show invalid line
        return -1;
    }

    return 0;
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

void parsing_textute_and_color(t_data *data, int fd)
{
    printf ("halawa\n");
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (*line == '\n') // Skip empty lines
        {
            free(line);
            continue;
        }

        if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
        {
            if (store_texture(data, line) != 0)
            {
                printf("Error\n  Invalid texture line\n");
                free(line);
                exit(1);
            }
        }
        else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
            store_colors(data, line);
        // parsing map
        else if (ft_strchr(" 01", line[0]))
        {
            // free(line);
            // parsing_map(data, fd, line);
            // break;
            printf("Map parsing not implemented yet.\n");
            free(line);
            exit(1);
        }
        else
        {
            printf("Error\n  Invalid line: %s", line);
            free(line);
            exit(1);
        }
        
        // if (data->path_no && data->path_so && data->path_we && data->path_ea &&
        //     data->floor_color != -1 && data->ceiling_color != -1)
        //     break;
        
        free(line);
    }

}
