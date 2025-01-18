/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:46:39 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/18 12:42:07 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	draw_minimap(t_data *data, int start_x, int start_y)
{
	int	y;
	int	x;
	int	dx;
	int	dy;

	y = -1;
	while (++y < MINIMAP_SIZE)
	{
		x = -1;
        while (++x < MINIMAP_SIZE)
		{
        	dx = x - MINIMAP_SIZE / 2;
            dy = y - MINIMAP_SIZE / 2;
            if (dx * dx + dy * dy <= MINIMAP_SIZE / 2 * MINIMAP_SIZE / 2)
			{
                int map_x = start_x + (x / SCALE_FACTOR);
                int map_y = start_y + (y / SCALE_FACTOR);
                if (map_x >= 0 && map_x < data->map->WIDHT && map_y >= 0 && map_y < data->map->HEIGHT && map_x / TILE_SIZE <= ft_strlen(data->map->map[map_y / TILE_SIZE]))
				{
                    if (data->map->map[map_y / TILE_SIZE][map_x / TILE_SIZE] == '1')
                        mlx_put_pixel(data->map->mini_map, x, y, COLOR_WALL);
                    else
                        mlx_put_pixel(data->map->mini_map, x, y, COLOR_SPACE);
                }
            }
        }
    }
}

void render_minimap(t_data *data)
{
	int	visible_start_x;
	int	visible_start_y;

	mlx_delete_image(data->map->mlx, data->map->mini_map);
	data->map->mini_map = mlx_new_image(data->map->mlx, MINIMAP_SIZE, MINIMAP_SIZE);
	mlx_image_to_window(data->map->mlx, data->map->mini_map, 0, WIN_HEIGHT - MINIMAP_SIZE);
    visible_start_x = data->player->pl->instances->x - (MINIMAP_SIZE / 2) / SCALE_FACTOR;
    visible_start_y = data->player->pl->instances->y - (MINIMAP_SIZE / 2) / SCALE_FACTOR;
	if (visible_start_x < 0)
		visible_start_x = 0;
	if (visible_start_y < 0)
		visible_start_y = 0;
	draw_minimap(data, visible_start_x, visible_start_y);
    mlx_put_pixel(data->map->mini_map, MINIMAP_SIZE / 2, MINIMAP_SIZE / 2, MAIN_COLOR);
}

/* void	render_map(t_data *data)
{
	int			y;
	int			x;
	int			py;
	int			px;
	uint32_t	color;

	y = -1;
	while (data->map->map[++y] != NULL)
	{
		x = -1;
		while (data->map->map[y][++x])
		{
			color = 0x00000000;
			if (data->map->map[y][x] != '1' && data->map->map[y][x] != ' ')
				color = COLOR_WALL;
			py = -1;
			while (++py < TILE_SIZE)
			{
				px = -1;
				while (++px < TILE_SIZE)
					mlx_put_pixel(data->map->mini_map, (x * TILE_SIZE + px)
						* MINIMAP_SCALE_FACTOR, (y * TILE_SIZE + py) * MINIMAP_SCALE_FACTOR, color);
			}
		}
	}
} */

void	render_rays(t_data *data, double x1, double y1)
{
	draw_line(data->player->ray,
		data->player->pl->instances->x * MINIMAP_SCALE_FACTOR,
		data->player->pl->instances->y * MINIMAP_SCALE_FACTOR,
		x1 * MINIMAP_SCALE_FACTOR, y1 * MINIMAP_SCALE_FACTOR,
		MAIN_COLOR);
}

void	render_3d_projection_walls(t_ray **rays, t_data *data)
{
	int		i;
	t_ray	*ray;
	int		wall_strip_height;
	double	correct_ray_dist;
	double	distance_projection_plane;

	i = -1;
	clear_image(data->map->img);
	while (++i < WIN_WIDTH)
	{
		ray = rays[i];
		correct_ray_dist = ray->distance
			* cos(ray->ray_angle - data->player->rotation_angle);
		distance_projection_plane = (WIN_WIDTH / 2)
			/ tan(data->player->FOV / 2);
		wall_strip_height = (TILE_SIZE / correct_ray_dist)
			* distance_projection_plane;
		draw_rectangle(data->map->img, i,
			(WIN_HEIGHT / 2) - (wall_strip_height / 2),
			1,
			wall_strip_height,
			ray->was_vert ? MAIN_COLOR : 0xf5f3f4FF);
	}
	i = -1;
	while (++i < WIN_WIDTH)
		free(rays[i]);
}
