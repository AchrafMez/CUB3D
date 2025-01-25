/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:32:08 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/25 11:09:08 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	free_txtr(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->map->textures[i])
			mlx_delete_texture(data->map->textures[i]);
	}
}

void	_set_points(double *points, t_ray *ray)
{
	if (ray->flg)
	{
		ray->horz_wall_hit_x = points[0];
		ray->horz_wall_hit_y = points[1];
	}
	else
	{
		ray->vert_wall_hit_x = points[0];
		ray->vert_wall_hit_y = points[1];
	}
	free(points);
}

int	print_error(int err)
{
	if (err == 1)
		write(STDERR_FILENO, "Failed to initialize MLX\n", 26);
	return (EXIT_FAILURE);
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
