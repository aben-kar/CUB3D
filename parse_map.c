/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:18:43 by achraf            #+#    #+#             */
/*   Updated: 2025/09/23 00:15:43 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

// void replace_espace(t_data *data)
// {
//     int i = 0;
//     int player = 0;
//     while (data->map[i])
//     {
//         int j = 0;
//         while (data->map[i][j])
//         {
//             if (data->map[i][j] == ' ')
//                 data->map[i][j] = '1';
//             else if (data->map[i][j] == "N" || data->map[i][j] == "S" ||
//                      data->map[i][j] == "E" || data->map[i][j] == "W")
//                 player++;
//             j++;
//         }
//         i++;
//     }
//     if (player > 1)
//     {
//         printf ("Error:\nThe map must contain one player starting position\n");
//         exit(1);
//     }
// }

void parse_map(t_data *data, int fd)
{
    char *line;
    
    line = get_next_line(fd);
    while (line)
    {
        if (line[0] == '\n')
        {
            free(line);
            print_error_and_exit("Map contains empty lines");
        }
        
        line = get_next_line(fd);
    }
}