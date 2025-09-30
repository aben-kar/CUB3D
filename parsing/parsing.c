/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/29 17:43:04 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void init_data(t_data *data)
{
    data->path_no = NULL;
    data->path_so = NULL;
    data->path_we = NULL;
    data->path_ea = NULL;
    data->floor_color = 0;
    data->ceiling_color = 0;
    data->map = NULL;
}

void parsing_cub(t_data *data, int fd)
{
    init_data(data);
    parse_texture_and_color(data, fd);
    parse_map(data, fd);
    is_map_valid(data);
}
