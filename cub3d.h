/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acben-ka <acben-ka@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:11:51 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/14 16:29:47 by acben-ka         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdbool.h>
#include "libs/libft/libft.h"
#include "libs/get_next_line/get_next_line_bonus.h"

typedef struct s_data
{
    char *path_no;
    char *path_so;
    char *path_we;
    char *path_ea;
    int floor_color;
    int ceiling_color;
    char **map;
} t_data;


// Function declarations
void parsing_textute_and_color(t_data *data, int fd);
// void validate_parsing(t_data *data);
// void parsing_map(t_data *data, int fd);

#endif