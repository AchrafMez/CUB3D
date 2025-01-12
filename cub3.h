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
#include <float.h>
#include "./MLX42/include/MLX42/MLX42.h"
#define TILE_SIZE 64
#define COLOR_GREEN 0x0F000FF
#define MAIN_COLOR 0x98FF98
#define COLOR_WALL 0x6468699B
#define COLOR_SPACE 0x37373737
#define PI 3.14159265358979323846
#define WALL_STRIP_WIDTH 1
#define LINE_LENGTH 30
#define MINIMAP_SCALE_FACTOR 0.2

typedef struct	s_player {
	float	x;
	float	y;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
	double	FOV;
	mlx_image_t	*pl;
	mlx_image_t	*line;
	mlx_image_t	*ray;
}				t_player;

typedef struct	s_ray
{
	float	wall_hit_X;
	float	wall_hit_Y;
	float	distance;
	float	ray_angle;
	int		ray_facing_down;
	int		ray_facing_up;
	int		ray_facing_right;
	int		ray_facing_left;
}				t_ray;

typedef struct	s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*mini_map;
	mlx_image_t	*img;
	int			win_width;
	int			win_height;
	char		**map;
	t_player	*player;
	t_ray		*rays;
}				t_cub;

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
