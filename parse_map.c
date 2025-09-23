/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 23:18:43 by achraf            #+#    #+#             */
/*   Updated: 2025/09/23 23:09:57 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub3d.h"

int is_map_line(char *line)
{
    int i = 0;

    while (line[i] && line[i] == ' ')
        i++;

    if (!line[i] || line[i] == '\n')
        return 0;

    while (line[i])
    {
        if (line[i] == '\n')
            break;
        if (!ft_strchr("01NSEW ", line[i]))
            return 0;
        i++;
    }
    return 1;
}

void parse_map_line(t_data *data, char *line)
{
    char *map_line = ft_strdup(line);


    if (!map_line)
    {
        printf("Memory allocation error\n");
        exit(1);
    }

    int len = ft_strlen(map_line);
    if (len > 0 && map_line[len - 1] == '\n')
        map_line[len - 1] = '\0';

    int map_size = 0;
    if (data->map)
    {
        while (data->map[map_size])
            map_size++;
    }

    char **new_map = (char **)malloc(sizeof(char *) * (map_size + 2));
    if (!new_map)
    {
        printf("Memory allocation error\n");
        free(map_line);
        exit(1);
    }

    for (int i = 0; i < map_size; i++)
        new_map[i] = data->map[i];
    new_map[map_size] = map_line;
    new_map[map_size + 1] = NULL;

    free(data->map);
    data->map = new_map;
}

void free_map(t_data *data)
{
    int i = 0;
    
    if (!data->map)
        return;
    while (data->map[i])
    {
        free(data->map[i]);
        i++;
    }
    free(data->map);
    data->map = NULL;
}

void map(t_data *data, char *line)
{
    int i = 0;
    
    if (!is_map_line(line))
    {
        free(line);
        print_error_and_exit("Invalid map line");
    }
    while (line[i])
    {
        // replace espace
        if (line[i] == ' ')
            line[i] = '1';
        i++;
    }
    parse_map_line(data, line);
}

void parse_map(t_data *data, int fd)
{
    char *line;
    int map_started = 0;  // flag bach n3raf wash l-map bdat
    
    line = get_next_line(fd);
    while (line)
    {
        if (line[0] == '\n')
        {
            if (map_started)
            {
                free(line);
                free_map(data);  // free l-map
                print_error_and_exit("Empty line found inside the map");
            }
            free(line);
            line = get_next_line(fd);
            continue;
        }
        map_started = 1;
        map(data, line);
        line = get_next_line(fd);
    }
    free(line);
}

void is_map_valid(t_data *data)
{
    if (!data->map || !data->map[0])
    print_error_and_exit("Map is empty");
    
    int i = 0;
    int player = 0;
    while (data->map[i])
    {
        int j = 0;
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
    {
        printf ("Error:\nThe map must contain one player starting position\n");
        exit(1);
    }

    int rows = 0;
    int cols = 0;
    while (data->map[rows])
    {
        int len = ft_strlen(data->map[rows]);
        if (len > cols)
            cols = len;
        rows++;
    }

    // check first row - koll character khass ykun '1'
    int first_row_len = ft_strlen(data->map[0]);
    for (int j = 0; j < first_row_len; j++)
    {
        if (data->map[0][j] != '1')
            print_error_and_exit("Map is not enclosed by walls (top row)");
    }
    
    // check last row - koll character khass ykun '1'
    int last_row_len = ft_strlen(data->map[rows - 1]);
    for (int j = 0; j < last_row_len; j++)
    {
        if (data->map[rows - 1][j] != '1')
            print_error_and_exit("Map is not enclosed by walls (bottom row)");
    }

    // check first and last column dyal koll row
    for (int i = 0; i < rows; i++)
    {
        int row_len = ft_strlen(data->map[i]);
        if (row_len == 0)
            continue;
            
        // check first character
        if (data->map[i][0] != '1')
            print_error_and_exit("Map is not enclosed by walls (left column)");
            
        // check last character
        if (data->map[i][row_len - 1] != '1')
            print_error_and_exit("Map is not enclosed by walls (right column)");
    }

}