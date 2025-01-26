/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_util2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 15:28:25 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/26 15:29:12 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

uint32_t	get_pixel_color(mlx_texture_t *tex, int tex_pos)
{
	return ((tex->pixels[tex_pos] << 24) 
		| (tex->pixels[tex_pos + 1] << 16) 
		| (tex->pixels[tex_pos + 2] << 8)
		| tex->pixels[tex_pos + 3]);
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
