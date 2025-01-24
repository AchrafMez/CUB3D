/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/23 18:32:08 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/24 10:04:20 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	mouse_handling(t_data *data)
{
	int32_t		x;
	int32_t		y;
	static int	pos;
	static int	last_y;

	x = 0;
	y = 0;
	mlx_get_mouse_pos(data->map->mlx, &x, &y);
	if (pos != 0)
		data->player->rotation_angle += (x - pos) * 0.001;
	if (last_y != 0)
		data->player->vertical -= (y - last_y) * 0.001;
	last_y = y;
	pos = x;
}

void	free_txtr(t_data *data)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (data->map->textures[i])
			mlx_delete_texture(data->map->textures[i]);
	}
	if (data->player->txr1)
		mlx_delete_texture(data->player->txr1);
	if (data->player->txr1)
		mlx_delete_texture(data->player->txr2);
	if (data->player->txr1)
		mlx_delete_texture(data->player->txr3);
	if (data->player->txr1)
		mlx_delete_texture(data->player->txr4);
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

void	load_textures(t_data *data)
{
	data->player->txr1 = mlx_load_png("./textures/1.png");
	if (!data->player->txr1)
	{
		write(STDERR_FILENO, "TXTR ERROR !!\n", 14);
		exit(1);
	}
	data->player->txr2 = mlx_load_png("./textures/2.png");
	if (!data->player->txr2)
	{
		write(STDERR_FILENO, "TXTR ERROR !!\n", 14);
		exit(1);
	}
	data->player->txr3 = mlx_load_png("./textures/3.png");
	if (!data->player->txr3)
	{
		write(STDERR_FILENO, "TXTR ERROR !!\n", 14);
		exit(1);
	}
	data->player->txr4 = mlx_load_png("./textures/4.png");
	if (!data->player->txr4)
	{
		write(STDERR_FILENO, "TXTR ERROR !!\n", 14);
		exit(1);
	}
}

int	print_error(int err)
{
	if (err == 1)
		write(STDERR_FILENO, "Failed to initialize MLX\n", 26);
	return (EXIT_FAILURE);
}
