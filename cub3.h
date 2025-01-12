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
	mlx_t	*mlx;
	mlx_image_t	*mini_map;
	mlx_image_t	*img;
} t_map;

typedef struct	s_data
{
	t_map		*map;
	t_player	*player;
	t_ray		*rays;
}				t_data;


void	player_init(t_player *pl, t_data *data);
int		is_collision(t_data *data, float new_X, float new_Y);
void	render_3d_projection_walls(t_ray **rays, t_data *data);
void	draw_rectangle(mlx_image_t *img, int x, int y, int width, int height, uint32_t color);
t_ray	**cast_all_rays(t_data *data);
t_ray	*create_Ray(float angle);
void	cast_rays(t_ray *ray, t_data *data);
double	distance_between_2_points(int32_t x1, int32_t y1, float x2, float y2);
void	render_rays(t_data *data, float x1, float y1);
void	clear_image(mlx_image_t *img);
float	normalize_angle(float angle);
int		is_WALL(t_data *data, int x, int y);
void	render_map(t_map *map);
int		raycast(t_data *data);

#endif
