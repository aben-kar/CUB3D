/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/24 13:58:55 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/25 22:34:03 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_multiple_player(t_data *data)
{
    if (!data->map || !data->map[0])
        return;
    int i;
    int j;
    int player;

    i = 0;
    player = 0;
    while (data->map[i])
    {
        j = 0;
        while (data->map[i][j])
        {
            if (data->map[i][j] == 'N' || data->map[i][j] == 'S' ||
                     data->map[i][j] == 'E' || data->map[i][j] == 'W')
                player++;
            j++;
        }
        i++;    
    }
    if (player > 1)
        print_error_and_exit("The map must contain one player starting position");
}

void is_map_closed(char **map)
{
    // for(int i = 0; map[i]; i++)
    //     printf ("%s\n", map[i]);
    if (!map || !map[0])
        return;
    
    int i;
    int rows;
    int first_row_len;
    int last_row_len;
    
    rows = 0;
    first_row_len = ft_strlen(map[0]);
    
    while (map[rows])
        rows++;
        
    i = 0;
    while (i < first_row_len)
    {
        if (map[0][i] != '1')
            print_error_and_exit("Map is not enclosed by walls (top row)");
        i++;
    }
    
    i = 0;
    last_row_len = ft_strlen(map[rows - 1]);
    while (i < last_row_len)
    {
        if (map[rows - 1][i] != '1')
            print_error_and_exit("Map is not enclosed by walls (bottom row)");
        i++;
    }

    i = 0;
    while (i < rows)
    {
        int row_len = ft_strlen(map[i]);
        
        if (map[i][0] != '1')
            print_error_and_exit("Map is not enclosed by walls (left column)");
        if (map[i][row_len - 1] != '1')
            print_error_and_exit("Map is not enclosed by walls (right column)");
        i++;
    }
}

void resize_map_rows(char **map)
{
    int i;
    int rows = 0;
    int cols = 0;

    while (map[rows])
    {
        int len = ft_strlen(map[rows]);
        if (len > cols)
            cols = len;
        rows++;
    }
    
    i = 0;
    while (map[i])
    {
        int len = ft_strlen(map[i]);
        if (len < cols)
        {
            char *new_line = (char *)malloc(sizeof(char) * (cols + 1));
            if (!new_line)
                print_error_and_exit("Memory allocation error");
            for (int j = 0; j < cols; j++)
            {
                if (j < len)
                    new_line[j] = map[i][j];
                else
                    new_line[j] = '?';
            }
            new_line[cols] = '\0';
            free(map[i]);
            map[i] = new_line;
        }
        i++;
    }
}