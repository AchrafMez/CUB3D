/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 10:09:34 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/21 13:30:02 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

uint32_t	get_rgb(int r, int g, int b, int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

int	is_WALL(t_data *data, int x, int y)
{
	int	X_index;
	int	Y_index;

	if (x < 0 || x >= data->map->WIDHT || y < 0 || y >= data->map->HEIGHT)
		return (1);
	Y_index = floor(y / TILE_SIZE);
	X_index = floor(x / TILE_SIZE);
	if (Y_index >= data->map->HEIGHT / TILE_SIZE || X_index >= data->map->WIDHT / TILE_SIZE)
		return (1);
	if (X_index >= ft_strlen(data->map->map[Y_index]))
		return (1);
	if (data->map->map[Y_index][X_index] == '1')
		return (1);
	return (0);
}

int	is_collision(t_data *data, double new_X, double new_Y)
{
	if (is_WALL(data, new_X - TILE_SIZE / 4, new_Y - TILE_SIZE / 4) ||
		is_WALL(data, new_X + TILE_SIZE / 4, new_Y - TILE_SIZE / 4) ||
		is_WALL(data, new_X - TILE_SIZE / 4, new_Y + TILE_SIZE / 4) ||
		is_WALL(data, new_X + TILE_SIZE / 4, new_Y + TILE_SIZE / 4))
		return (1);
	return (0);
}

double	dst_2_pts(int32_t x1, int32_t y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	normalize_angle(double angle)
{
	double	ret;

	ret = remainder(angle, (2 * M_PI));
	if (ret < 0)
		ret += (2 * M_PI);
	return (ret);
}
