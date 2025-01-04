#ifndef CUB3_H
# define CUB3_H

#include <stdio.h>
#include "./lib/lib.h"
#include "./getnextline/get_next_line.h"
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>



typedef struct s_map
{
    char *NO;
    char *SO;
    char *WE;
    char *EA;
    int *floor_rgb;
    int *ciel_rgb;
    char **map;
    int player_x;
    int player_y;
    int HEIGHT;
    int WIDHT;
    
} t_map;


#endif

//1111111111111111111111111
//1000000000110000000000001
//1011000001110000000000001
//01001000000000000000000001
//11111111101100000111000000000001
//10000000001100000111011111111111
//11000000110101011100000010001
//10000000000000001100000010001
//11110111111111011100000010001
//10000000000000001101010010001
//11000001110101011111011110N0111
//11110111 1110101 101111010001
//11111111 1111111 111111111111
