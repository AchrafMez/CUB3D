/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:31:49 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/25 10:51:55 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

t_ray	**cast_all_rays(t_data *data)
{
	double		ray_angle;
	int			i;
	t_player	*player;
	t_ray		**rays;
	t_ray		*ray;

	player = data->player;
	rays = malloc(sizeof(t_ray *) * WIN_WIDTH);
	ray_angle = player->rotation_angle - (player->fov / 2);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		ray = create_ray(ray_angle);
		cast_ray(ray, data);
		rays[i] = ray;
		ray_angle += player->fov / WIN_WIDTH;
	}
	return (rays);
}

void	_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_txtr(data);
	free(data->player);
}

int	raycast(t_data *data)
{
	t_player	*pl;

	pl = (t_player *)malloc(sizeof(t_player));
	player_init(pl, data);
	data->player = pl;
	data->map->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	if (!data->map->mlx)
	{
		free(pl);
		return (print_error(1));
	}
	load_tex(data);
	init_imgs(data, pl);
	mlx_loop_hook(data->map->mlx, render, data);
	mlx_close_hook(data->map->mlx, _close, data);
	mlx_loop(data->map->mlx);
	mlx_terminate(data->map->mlx);
	return (EXIT_SUCCESS);
}
