/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation_map_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/28 17:45:44 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/28 20:22:04 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

bool is_player(char position)
{
    return (position == 'N'
        || position == 'S'
        || position == 'W'
        || position == 'E');
}

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
        if (map[0][i] != '1' && map[0][i] != '?')
            print_error_and_exit("Map not closed");
        else
        {
            if (map[0][i] == '?')
            {
                if ((map[1][i] != '1' && map[1][i] != '?') && map[1][i])
                    print_error_and_exit("Map not closed");
            }
        }
        i++;
    }
    
    i = 0;
    last_row_len = ft_strlen(map[rows - 1]);
    while (i < last_row_len)
    {
        if (map[rows - 1][i] != '1' && map[rows - 1][i] != '?')
            print_error_and_exit("Map not closed");
        else
        {
            if (map[rows - 1][i] == '?')
            {
                if ((map[rows - 2][i] != '1' && map[rows - 2][i] != '?') && map[rows - 2][i])
                    print_error_and_exit("Map not closed");
            }
        }
        i++;
    }

    i = 0;
    int player = 0;
    while (i < rows)
    {
        int j = 0;
        while (map[i][j])
        {
            if (is_player(map[i][j]))
                player++;
            j++;
        }
        
        if (map[i][0] != '1')
            print_error_and_exit("Map not closed");
        else
        {
            int k = 0;
            while (map[i][k])
            {
                if (map[i][k] == '?')
                {
                    if ((map[i][k - 1] != '1' && map[i][k - 1] != '?') && k - 1 >= 0)
                        print_error_and_exit("Map not closed");
                    else if (i - 1 >= 0)
                    {
                        if ((map[i - 1][k] != '1' && map[i - 1][k] != '?') && map[i - 1][k])
                            print_error_and_exit("Map not closed");
                    }
                }
                else
                {
                    int len = ft_strlen(map[i]);
                    if (map[i][len - 1] != '1' && map[i][len - 1] != '?')
                        print_error_and_exit("Map not closed");
                }
                k++; 
            }
        }    
        i++;
    }
    if (player != 1)
        print_error_and_exit("The map must contain one player starting position");
}
