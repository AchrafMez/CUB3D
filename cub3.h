/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 09:45:56 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/20 21:16:26 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3_H
# define CUB3_H

#include <stdio.h>
#include <unistd.h>
#include "./lib/lib.h"
#include "./getnextline/get_next_line.h"
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>   
#include <float.h>
#include "./MLX42/include/MLX42/MLX42.h"

#define TILE_SIZE 32
#define WIN_WIDTH 1180
#define	WIN_HEIGHT 820
#define MAIN_COLOR 0xd3d3d3FF
#define COLOR_WALL 0x6468699B
#define COLOR_SPACE 0x37373737
#define MINIMAP_SCALE_FACTOR 0.2
#define MINIMAP_SIZE 150
#define SCALE_FACTOR 0.3

typedef struct	s_player {
	double	x;
	double	y;
	int		turn_direction;
	int		walk_direction;
	bool	walk;
	double	rotation_angle;
	double	move_speed;
	double	rotation_speed;
	double	side_angle;
	double	FOV;
	mlx_image_t	*pl;
	mlx_image_t	*ray;
	mlx_texture_t	*txr;
	mlx_texture_t	*txr1;
	mlx_texture_t	*txr2;
	mlx_texture_t	*txr3;
	mlx_image_t		*tt;
	mlx_image_t		*tt1;
	mlx_image_t		*tt2;
	mlx_image_t		*tt3;;
}				t_player;

typedef struct	s_ray
{
	double	wall_hit_X;
	double	wall_hit_Y;
	double	distance;
	double	ray_angle;
	int		ray_facing_down;
	int		ray_facing_up;
	int		ray_facing_right;
	int		ray_facing_left;
	bool	was_vert;
	bool	found_vert_hit;
	bool	found_horz_hit;
}				t_ray;

typedef struct s_map
{
    char player;
    const char *NO;
    const char *SO;
    const char *WE;
    const char *EA;
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
	mlx_image_t	*background;
	mlx_texture_t *textures[4];
} t_map;

typedef struct	s_data
{
	t_map		*map;
	t_player	*player;
	t_ray		*rays;
}				t_data;


//config
void free_fc(char **fc);
void fre_maplines(char **map);
void free_map(t_map *map);
void ft_exit(char *str ,t_map *map);


void store_textures(char index, char *line, t_map **map);
int check_texture_perm(char *path);


void store_FC(char **fc, int flag, t_map **map);
int check_fc_prototype(char *line, t_map *map);
int check_FC(char *line, t_map *map);
void fill_colors(char *line, t_map **map, int flag);

void print_map(t_map *map);
void print_maplines(char **map);



int check_extension(char *file_name);
int check_positions(char *line, char f, char s, t_map **map);
int check_identif(char *line);
int check_color(char *fc, t_map *map);

//init
void null_init(t_map *map);
void init_floor(t_map **map);
void init_ciel(t_map **map);

//is_valid
int valide_color(char **fc, t_map *map);
int valid_color(char *line);
int valid_map(char *line);


//check_map
int check_map_walls(char **map);
void check_filled_map(t_map *map);
void check_ones(char *line, t_map *map);
int check_map_chars(t_map *map);
void check_zeros(t_map *map, int i, int j);
void check_map_spaces(t_map *map);


//read map
void read_map(char *file_name, t_map **map);

//parse
void parse_colors(char *line, t_map **map);
int is_map(char *line);
int empty_line(char *line);
int wall(char *map);
void WHXY(t_map **map);

//fill map
void fill_mapline(int map_line, int fd, t_map **map);
void fill_map(int fd, char *file_namp, t_map **map);

//map line
int lines_count(int fd, t_map *map);
int map_lines(int fd, t_map *map);



void		player_init(t_player *pl, t_data *data);
int			is_collision(t_data *data, double new_X, double new_Y);
void		render_3d_projection_walls(t_ray **rays, t_data *data);
void		draw_rectangle(mlx_image_t *img, int x, int y, int width, int height, uint32_t color);
t_ray		**cast_all_rays(t_data *data);
t_ray		*create_Ray(double angle);
void		cast_ray(t_ray *ray, t_data *data);
double		distance_between_2_points(int32_t x1, int32_t y1, double x2, double y2);
void		render_rays(t_data *data, double x1, double y1);
void		clear_image(mlx_image_t *img);
double		normalize_angle(double angle);
int			is_WALL(t_data *data, int x, int y);
void		render_map(t_data *data);
int			raycast(t_data *data);
void		draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color);
uint32_t	get_rgb(int r, int g, int b);
void		color_background(mlx_image_t *bg, t_map *map);
void	render_minimap(t_data *data);
void render_walls(t_ray **rays, t_data *data);
void load_tex(t_data *data);

#endif
