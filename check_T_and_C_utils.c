/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_T_and_C_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 18:46:09 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/08 19:03:42 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_valid_texture(char *line)
{
    if (!line)
        return 0;
    if (ft_strncmp(line, "NO ", 3) == 0 || ft_strncmp(line, "SO ", 3) == 0 ||
        ft_strncmp(line, "WE ", 3) == 0 || ft_strncmp(line, "EA ", 3) == 0)
        return 1;
    return 0;
}