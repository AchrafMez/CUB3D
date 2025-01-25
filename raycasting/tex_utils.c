/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:48:09 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 04:56:17 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	load_tex(t_data *data)
{
	t_map	*map;

	map = data->map;
	map->textures[0] = mlx_load_png(map->SO);
	map->textures[1] = mlx_load_png(map->NO);
	map->textures[2] = mlx_load_png(map->WE);
	map->textures[3] = mlx_load_png(map->EA);
	if (!map->textures[0] || !map->textures[1] || !map->textures[2]
		|| !map->textures[3])
		exit(1);
}

float	calc_tex_x_vertical(t_ray *ray, float tex_width)
{
	float	tex_x;

	tex_x = ray->wall_hit_y;
	tex_x = fmod(tex_x, TILE_SIZE);
	if (tex_x < 0)
		tex_x += TILE_SIZE;
	tex_x = (tex_x * tex_width) / TILE_SIZE;
	if (ray->ray_facing_left)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

float	calc_tex_x_horizontal(t_ray *ray, float tex_width)
{
	float	tex_x;

	tex_x = ray->wall_hit_x;
	tex_x = fmod(tex_x, TILE_SIZE);
	if (tex_x < 0)
		tex_x += TILE_SIZE;
	tex_x = (tex_x * tex_width) / TILE_SIZE;
	if (!ray->ray_facing_up)
		tex_x = tex_width - tex_x - 1;
	return (tex_x);
}

float	get_tex_x(t_ray *ray, mlx_texture_t *tex)
{
	float	tex_x;
	float	tex_width;

	tex_width = (float)tex->width;
	if (ray->was_vert)
		tex_x = calc_tex_x_vertical(ray, tex_width);
	else
		tex_x = calc_tex_x_horizontal(ray, tex_width);
	if (tex_x >= tex_width)
		tex_x = tex_width - 1;
	if (tex_x < 0)
		tex_x = 0;
	return (tex_x);
}

uint32_t	get_pixel_color(mlx_texture_t *tex, int tex_pos)
{
	return ((tex->pixels[tex_pos] << 24) 
		| (tex->pixels[tex_pos + 1] << 16) 
		| (tex->pixels[tex_pos + 2] << 8)
		| tex->pixels[tex_pos + 3]);
}
