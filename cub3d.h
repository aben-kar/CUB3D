/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: achraf <achraf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 15:11:51 by acben-ka          #+#    #+#             */
/*   Updated: 2025/09/23 00:14:58 by achraf           ###   ########.fr       */
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
void parsing_texture_and_color(t_data *data, int fd);
void parse_texture_and_color(t_data *data, int fd);
void    parse_config_file(t_data *data, char *line);
int all_config_parsed(t_data *data);
int extract_rgb_color(char *line);
void free_split(char **split);
void print_error_and_exit(const char *msg);

#endif