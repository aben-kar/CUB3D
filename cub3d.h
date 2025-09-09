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
} t_data;


// Function declarations
void parsing_cub(t_data *data, int fd);
int is_valid_texture(char *line);
int is_valid_space(char *line);
int is_valid_path(char *line);

#endif