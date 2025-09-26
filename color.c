/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:49:10 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/26 20:45:28 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_is_rgb_digit(char **rgb_values)
{
    int i;

    i = 0;
    while (i < 3)
    {
        int j;

        j = 0;
        while (rgb_values[i][j])
        {
            if (!ft_isdigit(rgb_values[i][j]))
            {
                print_error_and_exit("RGB values must contain only digits");
                free_split(rgb_values);
            }
            j++;
        }
        i++;
    }
}

int extract_rgb_color(char *line)
{
    char **rgb_values;
    int r, g, b;
    int color;
    char *cleand;

    cleand = clean_line(line);
    rgb_values = ft_split(cleand, ',');
    free(cleand);
    
    if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3] != NULL)
    {
        printf("Error\n  Invalid color format\n");
        free_split(rgb_values);
        exit(1);
    }
    check_is_rgb_digit(rgb_values);
    r = ft_atoi(rgb_values[0]);
    g = ft_atoi(rgb_values[1]);
    b = ft_atoi(rgb_values[2]);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
    {
        print_error_and_exit("Color values must be between 0 and 255");
        free_split(rgb_values);
    }
    color = (r << 16) | (g << 8) | b;
    free_split(rgb_values);
    return (color);
}
