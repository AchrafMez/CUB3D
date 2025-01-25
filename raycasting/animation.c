/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:25:59 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/24 11:57:42 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	sprite_player(t_data *data)
{
	if (data->player->gun)
		mlx_delete_image(data->map->mlx, data->player->gun);
	if (data->animation.current_frame == 0)
		data->player->gun = mlx_texture_to_image(data->map->mlx,
				data->player->txr1);
	else if (data->animation.current_frame == 1)
		data->player->gun = mlx_texture_to_image(data->map->mlx,
				data->player->txr2);
	else if (data->animation.current_frame == 2)
		data->player->gun = mlx_texture_to_image(data->map->mlx,
				data->player->txr3);
	else if (data->animation.current_frame == 3)
		data->player->gun = mlx_texture_to_image(data->map->mlx,
				data->player->txr1);
	mlx_image_to_window(data->map->mlx, data->player->gun,
		WIN_WIDTH / 2.5, WIN_HEIGHT - 106 * 2.5);
	mlx_resize_image(data->player->gun, 91 * 2.5, 106 * 2.5);
}

void	gun_animation(t_data *data)
{
	if (mlx_is_mouse_down(data->map->mlx, MLX_MOUSE_BUTTON_LEFT)
		&& !data->animation.is_active)
	{
		data->animation.is_active = 1;
		data->animation.current_frame = 0;
		data->animation.frame_counter = 0;
	}
	if (data->animation.is_active)
	{
		data->animation.frame_counter++;
		if (data->animation.frame_counter >= data->animation.frame_delay)
		{
			data->animation.frame_counter = 0;
			sprite_player(data);
			data->animation.current_frame++;
			if (data->animation.current_frame > 3)
			{
				data->animation.is_active = 0;
				data->animation.current_frame = 0;
			}
		}
	}
}
