/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/22 15:49:10 by acben-ka          #+#    #+#             */
/*   Updated: 2025/10/16 12:34:28 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

void check_is_rgb_digit(char **rgb_values)
{
    if (!rgb_values || !*rgb_values)
        return;
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
                // free_split(rgb_values);
            }
            j++;
        }
        i++;
    }
}



int extract_rgb_color(char *line, t_gc **gc)
{
    if (!line || !line[0])
        return (0);
    char **rgb_values;
    int r, g, b;
    int color;
    int count_virgule = 0;
    char *cleand;

    int i = 0;
    while (line[i])
    {
        if (line[i] == ',')
            count_virgule++;
        i++;
    }
    if (count_virgule > 2)
        print_error_and_exit("Invalid color format");

    cleand = ft_strtrim_gc(line, "\n", gc);
    rgb_values = ft_split_gc(cleand, ",", gc);
    
    if (!rgb_values || !rgb_values[0] || !rgb_values[1] || !rgb_values[2] || rgb_values[3] != NULL)
        print_error_and_exit("Invalid color format");
    check_is_rgb_digit(rgb_values);
    r = ft_atoi(rgb_values[0]);
    g = ft_atoi(rgb_values[1]);
    b = ft_atoi(rgb_values[2]);

    if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
        print_error_and_exit("Color values must be between 0 and 255");
    color = (r << 16) | (g << 8) | b;
    return (color);
}
