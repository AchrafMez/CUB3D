/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:29:59 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/25 06:51:05 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	_set_player_pos(t_data *data, int32_t x, int32_t y)
{
	if (!is_collision(data, x, y))
	{
		data->player->pl->instances->x = x;
		data->player->pl->instances->y = y;
	}
}

void	update_player_pos(t_data *data)
{
	t_player	*player;
	int32_t		new_x;
	int32_t		new_y;
	double		move_step;

	player = data->player;
	player->rotation_angle += player->turn_direction * player->rotation_speed;
	move_step = player->walk_direction * player->move_speed;
	if (player->walk)
	{
		player->side_angle = player->rotation_angle + (M_PI / 2);
		new_x = player->pl->instances->x
			+ round(cos(player->side_angle) * move_step);
		new_y = player->pl->instances->y
			+ round(sin(player->side_angle) * move_step);
		player->walk = false;
	}
	else
	{
		new_x = player->pl->instances->x
			+ round(cos(player->rotation_angle) * move_step);
		new_y = player->pl->instances->y
			+ round(sin(player->rotation_angle) * move_step);
	}
	_set_player_pos(data, new_x, new_y);
}

void	render_all(t_data *data)
{
	t_ray	**rays;
	int		i;

	render_minimap(data);
	gun_animation(data);
	update_player_pos(data);
	mouse_handling(data);
	rays = cast_all_rays(data);
	render_walls(rays, data);
	i = -1;
	while (++i < WIN_WIDTH)
		free(rays[i]);
	free(rays);
}

void	ft_keys(t_data *data)
{
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_W))
		data->player->walk_direction = 1;
	else if (mlx_is_key_down(data->map->mlx, MLX_KEY_S))
		data->player->walk_direction = -1;
	else if (mlx_is_key_down(data->map->mlx, MLX_KEY_A))
	{
		data->player->walk = true;
		data->player->walk_direction = -1;
	}
	else if (mlx_is_key_down(data->map->mlx, MLX_KEY_D))
	{
		data->player->walk = true;
		data->player->walk_direction = 1;
	}
	else
		data->player->walk_direction = 0;
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_RIGHT))
		data->player->turn_direction = 1;
	else if (mlx_is_key_down(data->map->mlx, MLX_KEY_LEFT))
		data->player->turn_direction = -1;
	else
		data->player->turn_direction = 0;
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
