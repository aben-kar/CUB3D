#ifndef CUB_H
#define CUB_H

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "get_next_line/get_next_line_bonus.h"

// Function declarations
void check_texture_and_color(int fd);
int is_valid_texture(char *line);

#endif