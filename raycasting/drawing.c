/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:19:04 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/21 10:38:57 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	draw_rectangle(mlx_image_t *img, int x, int y, int width, int height, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (x + j >= 0 && (uint32_t)(x + j) < img->width
				&& (uint32_t)(y + i) >= 0 && (uint32_t)(y + i) < img->height)
                mlx_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
}

void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
	int dx;
	int dy;
	int	i;

	dx = x1- x0;
	dy = y1 - y0;
	i = -1;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	double x_inc = dx / (double)steps;
	double y_inc = dy / (double)steps;

	double x = x0;
	double y = y0;
	while (++i <= steps)
	{
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			mlx_put_pixel(img, (int)round(x), (int)round(y), color);
		x += x_inc;
		y += y_inc;
	}
}

void	clear_image(mlx_image_t *img)
{
	int	y;
	int	x;

	y = 0;
	while ((uint32_t)y < img->height)
	{
		x = 0;
		while ((uint32_t)x < img->width)
		{
			mlx_put_pixel(img, x, y, 0x00000000);
			x++;
		}
		y++;
	}
}

void	bg_coloring(mlx_image_t *bg, t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while ((uint32_t)(++y) < bg->height / 2)
	{
		x = -1;
		while ((uint32_t)++x < bg->width)
			mlx_put_pixel(bg, x, y, get_rgb(map->ciel_rgb[0], map->ciel_rgb[1], map->ciel_rgb[2], 255));
	}
	y = bg->height / 2;
	while ((uint32_t)++y < bg->height)
	{
		x = -1;
		while ((uint32_t)++x < bg->width)
			mlx_put_pixel(bg, x, y, get_rgb(map->floor_rgb[0], map->floor_rgb[1], map->floor_rgb[2], 255));
	}
}
