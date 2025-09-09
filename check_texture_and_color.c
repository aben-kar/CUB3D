/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_and_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/09 21:01:48 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void parsing_cub(t_data *data, int fd)
{
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (is_valid_texture(line) == 1)
        {
            printf ("2\n");
            // Store the texture path in the data structure
            if (ft_strncmp(line, "NO ", 3) == 0)
                data->path_no = ft_strdup(line + 3);
            else if (ft_strncmp(line, "SO ", 3) == 0)
                data->path_so = ft_strdup(line + 3);
            else if (ft_strncmp(line, "WE ", 3) == 0)
                data->path_we = ft_strdup(line + 3);
            else if (ft_strncmp(line, "EA ", 3) == 0)
                data->path_ea = ft_strdup(line + 3);
        }
        else
        {
            printf("Error: Invalid texture line\n");
            free(line);
            return;
        }
        free(line);
    }
}