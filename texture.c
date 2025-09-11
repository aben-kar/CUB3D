/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/11 16:09:53 by acben-ka         ###   ########.fr       */
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

// int parse_texture(char *line)
// {
//     int result = 0;
//     if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
//         ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0 || ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
//     {
//         if (is_valid_space(line))
//             return 0;
//         result = 1;
//     }
//     return result;
// }
char *parse_texture(char *line)
{
    char *path;

    // Skip the identifier (e.g., "NO ", "SO ", etc.)
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
    printf("Debug: Parsing line -> %s\n", line); // Debug line

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
    printf("alooooooooo\n");
    char **rgb_values;
    int r, g, b;
    int color;

    line += 2;
    rgb_values = ft_split(line, ',');
    printf("rgb ==> %s\n", rgb_values[0]);
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
        printf("dkhol\n");
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

// void parsing_cub(t_data *data, int fd)
// {
//     char *line;
//     while ((line = get_next_line(fd)) != NULL)
//     {
//         if (*line == '\n')
//         {
//             free(line);
//             continue;
//         }
//         printf("Valid texture line: %s", line);
//         store_texture(data, line);
//         store_colors(data, line);
//         free(line);
//     }
// }

void parsing_cub(t_data *data, int fd)
{
    char *line;
    int texture_stored = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        if (*line == '\n') // Skip empty lines
        {
            free(line);
            continue;
        }

        // Check if the line is a texture line
        if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
            ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
        {
            if (store_texture(data, line) == 0) // Store texture
                texture_stored = 1;
            else
            {
                printf("Error\n  Invalid texture line\n");
                free(line);
                exit(1);
            }
        }
        // Check if the line is a color line
        else if (ft_strncmp(line, "F ", 2) == 0 || ft_strncmp(line, "C ", 2) == 0)
        {
            store_colors(data, line); // Store floor/ceiling colors
        }
        else
        {
            printf("Error\n  Invalid line: %s\n", line);
            free(line);
            exit(1);
        }

        free(line);
    }

    if (!texture_stored) // Ensure at least one texture is stored
    {
        printf("Error\n  No valid texture found\n");
        exit(1);
    }
}