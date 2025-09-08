/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_texture_and_color.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 17:16:08 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/08 19:04:26 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void check_texture_and_color(int fd)
{
    char *line;
    while ((line = get_next_line(fd)) != NULL)
    {
        if (!line)
            return ;
        // valid texture and color
        if (ft_strncmp(line, "NO", 2) == 0 || ft_strncmp(line, "SO", 2) == 0 || 
        ft_strncmp(line, "WE", 2) == 0 || ft_strncmp(line, "EA", 2) == 0)
        {
            if (is_valid_texture(line))
            {
                // store texture in struct
                
                printf("Valid texture\n");
            }
            else
            {
                printf("Error\n  Invalid texture line\n");
                // free(line);
                // exit(1);
            }
            
        }
        else 
            printf ("makayench\n");

        free(line);
    }
}