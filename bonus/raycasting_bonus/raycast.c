/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:31:49 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/26 13:21:30 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

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

void	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_ESCAPE))
	{
		free_txtr(data);
		free(data->player);
		mlx_close_window(data->map->mlx);
		return ;
	}
	ft_keys(data);
	render_all(data);
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
	data->animation = (t_animation){.current_frame = 0, .is_active = 0,
		.frame_delay = 2, .frame_counter = 0, .move = 0};
	load_tex(data);
	init_imgs(data, pl);
	mlx_loop_hook(data->map->mlx, render, data);
	mlx_close_hook(data->map->mlx, _close, data);
	mlx_loop(data->map->mlx);
	mlx_terminate(data->map->mlx);
	return (EXIT_SUCCESS);
}
