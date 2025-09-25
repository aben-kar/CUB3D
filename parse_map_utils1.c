#include "cub3d.h"

static bool is_player(char position)
{
    return (position == 'N'
        || position == 'S'
        || position == 'W'
        || position == 'E');
}

void validation_map(char **map)
{
    is_map_closed(map);
    resize_map_rows(map);

    int i = 0;
    int player = 0;
    while (map[i])
    {
        int k = 0;

        while (map[i][k])
        {
            if (is_player(map[i][k]))
                player++;
            else if (map[i][k] == '?')
            {
                if ((map[i - 1][k] != '1' && map[i - 1][k] != '?') && map[i][k])
                    print_error_and_exit("Map not close");
            }
            k++;
        } 
        i++;
    }
    if (player != 1)
        print_error_and_exit("The map must contain one player starting position");
}