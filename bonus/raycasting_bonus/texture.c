/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:53:02 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:23:07 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	draw_tex_helper(t_tex_params *p, int tex_x_pixel, int draw_start)
{
	int			tex_y_pixel;
	int			tex_pos;
	uint32_t	color;

	tex_y_pixel = (int)(((float)(draw_start - 1 - p->wall_top) / p->wall_height)
			* p->tex->height);
	if (tex_y_pixel < 0)
		tex_y_pixel = 0;
	else if ((uint16_t)tex_y_pixel >= p->tex->height)
		tex_y_pixel = p->tex->height - 1;
	tex_pos = (tex_y_pixel * p->tex->width + tex_x_pixel)
		* p->tex->bytes_per_pixel;
	color = get_pixel_color(p->tex, tex_pos);
	if (p->x >= 0 && p->x < WIN_WIDTH && draw_start - 1 >= 0 && draw_start
		- 1 < WIN_HEIGHT)
		mlx_put_pixel(p->data->map->img, p->x, draw_start - 1, color);
}

void	draw_tex(t_tex_params *p)
{
	int	draw_start;
	int	draw_end;
	int	tex_x_pixel;

	draw_start = 0;
	draw_end = 0;
	tex_x_pixel = 0;
	adjust_draw_bounds(p, &draw_start, &draw_end);
	tex_x_pixel = get_tex_x_pixel(p->tex_x, p->tex);
	while (draw_start++ <= draw_end)
		draw_tex_helper(p, tex_x_pixel, draw_start);
}

void	draw_fc(t_data *data, int vertical)
{
	int			x;
	int			y;
	int			adjusted_y;
	uint32_t	ceil_color;
	uint32_t	floor_color;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			adjusted_y = y - vertical;
			ceil_color = get_rgb_color(data->map->ciel_rgb);
			if (adjusted_y < WIN_HEIGHT / 2)
				mlx_put_pixel(data->map->img, x, y, ceil_color);
			else
			{
				floor_color = get_rgb_color(data->map->floor_rgb);
				mlx_put_pixel(data->map->img, x, y, floor_color);
			}
			x++;
		}
		y++;
	}
}

static mlx_texture_t	*select_texture(t_ray *ray, t_data *data)
{
	if (ray->was_vert)
	{
		if (ray->ray_facing_left)
			return (data->map->textures[2]);
		return (data->map->textures[3]);
	}
	else
	{
		if (ray->ray_facing_up)
			return (data->map->textures[0]);
		return (data->map->textures[1]);
	}
}

void	render_walls(t_ray **rays, t_data *data)
{
	int				i;
	float			proj_plane_dist;
	int				vertical;
	t_ray			*ray;
	t_tex_params	p;

	i = -1;
	proj_plane_dist = (WIN_WIDTH / 2) / tan(data->player->fov / 2);
	vertical = (int)(WIN_HEIGHT * tan(data->player->vertical));
	clear_image(data->map->img);
	draw_fc(data, vertical);
	while (++i < WIN_WIDTH)
	{
		ray = rays[i];
		p.data = data;
		p.x = i;
		p.wall_height = (int)((float)TILE_SIZE / (ray->distance
					* cos(ray->ray_angle - data->player->rotation_angle))
				* proj_plane_dist);
		p.wall_top = (WIN_HEIGHT / 2) - (p.wall_height / 2) + vertical;
		p.tex = select_texture(ray, data);
		p.tex_x = get_tex_x(ray, p.tex);
		draw_tex(&p);
	}
}
