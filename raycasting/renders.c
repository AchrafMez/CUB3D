/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renders.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:46:39 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/17 09:51:14 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	render_map(t_map *map)
{
	int			y;
	int			x;
	int			py;
	int			px;
	uint32_t	color;

	y = -1;
	while (map->map[++y] != NULL)
	{
		x = -1;
		while (map->map[y][++x])
		{
			color = 0x00000000;
			if (map->map[y][x] != '1' && map->map[y][x] != ' ')
				color = COLOR_WALL;
			py = -1;
			while (++py < TILE_SIZE)
			{
				px = -1;
				while (++px < TILE_SIZE)
					mlx_put_pixel(map->mini_map, (x * TILE_SIZE + px)
						* MINIMAP_SCALE_FACTOR, (y * TILE_SIZE + py) * MINIMAP_SCALE_FACTOR, color);
			}
		}
	}
}

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
