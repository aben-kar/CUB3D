/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:49:10 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/23 00:05:00 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int extract_rgb_color(char *line)
{
    char **rgb_values;
    int r, g, b;
    int color;
    char *clean_line;
    int len;

    len = ft_strlen(line);
    clean_line = ft_strdup(line);
    if (len > 0 && clean_line[len - 1] == '\n')
        clean_line[len - 1] = '\0';

    rgb_values = ft_split(clean_line, ',');
    free(clean_line);
    
    if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3] != NULL)
    {
        printf("Error\n  Invalid color format\n");
        free_split(rgb_values);
        exit(1);
    }

    for (int i = 0; i < 3; i++)
    {
        int j = 0;
        while (rgb_values[i][j])
        {
            if (!ft_isdigit(rgb_values[i][j]))
            {
                printf("Error\n  RGB values must contain only digits\n");
                free_split(rgb_values);
                exit(1);
            }
            j++;
        }
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