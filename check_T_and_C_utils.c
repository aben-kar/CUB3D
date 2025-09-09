/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_T_and_C_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:46:09 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/09 21:00:37 by achraf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_valid_texture(char *line)
{
    if (!line)
        return 0;
    if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
        ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
    {
        if (is_valid_space(line))
        {
            return 0;
        }
        // if (is_valid_path(line))
        //     return 0;
        return 1;
    }
    printf ("1\n");
    return 0;
}

int is_valid_space(char *line)
{
    int i = 0;
    while (line[i])
    {
        if (line[i] == ' ')
            i++;
        else
            break;
    }
    if (i > 2)
        return 1;
    return 0;
}

// int is_valid_path(char *line)
// {
//     char *path = line + 3;
//     while (*path == ' ')
//         path++;
//     char *newline = ft_strchr(path, '\n');
//     if (newline)
//         *newline = '\0';
//     int fd = open(path, O_RDONLY);
//     if (fd == -1)
//     {
//         perror("open"); // katban l error dyal open
//         return 1;
//     }
//     close(fd);
//     return 0;
// }