#ifndef CUB3_H
# define CUB3_H
#include <stdio.h>
#include "./getnextline/get_next_line.h"
#include "unistd.h"
#include "stdlib.h"

typedef struct s_map
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    char **map;
    int player_x;
    int player_y;
    
} t_map;


#endif