/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 10:11:42 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/26 23:12:20 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	player_init(t_player *pl, t_data *data)
{
	pl->walk_direction = 0;
	pl->turn_direction = 0;
	pl->vertical = 0.0;
	pl->walk = false;
	if (data->map->player == 'N')
		pl->rotation_angle = (3 * M_PI) / 2;
	if (data->map->player == 'W')
		pl->rotation_angle = M_PI;
	if (data->map->player == 'E')
		pl->rotation_angle = 0;
	if (data->map->player == 'S')
		pl->rotation_angle = M_PI / 2;
	pl->move_speed = 2.0;
	pl->rotation_speed = 2 * (M_PI / 180);
	pl->fov = 60 * (M_PI / 180);
	pl->side_angle = 0.0;
	pl->x = data->map->player_x * TILE_SIZE;
	pl->y = data->map->player_y * TILE_SIZE;
	data->map->width *= TILE_SIZE;
	data->map->height *= TILE_SIZE;
}

void	init_imgs(t_data *data, t_player *pl)
{
	data->map->background = mlx_new_image(data->map->mlx,
			WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(data->map->mlx, data->map->background, 0, 0);
	data->map->img = mlx_new_image(data->map->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(data->map->mlx, data->map->img, 0, 0);
	pl->pl = mlx_new_image(data->map->mlx, TILE_SIZE, TILE_SIZE);
	mlx_image_to_window(data->map->mlx, pl->pl,
		(pl->x + TILE_SIZE / 3), (pl->y + TILE_SIZE / 3));
	load_textures(data);
	data->player->gun = mlx_texture_to_image(data->map->mlx,
			data->player->txr1);
	mlx_image_to_window(data->map->mlx, data->player->gun,
		WIN_WIDTH / 2.5, WIN_HEIGHT - 106 * 2.5);
	mlx_resize_image(data->player->gun, 91 * 2.5, 106 * 2.5);
	mlx_set_cursor_mode(data->map->mlx, MLX_MOUSE_DISABLED);
}

t_ray	*create_ray(double angle)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->ray_angle = normalize_angle(angle);
	ray->distance = 0;
	ray->wall_hit_x = 0;
	ray->wall_hit_y = 0;
	ray->was_vert = false;
	ray->ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->ray_facing_up = !ray->ray_facing_down;
	ray->ray_facing_right = ray->ray_angle < 0.5 * M_PI 
		|| ray->ray_angle > (1.5 * M_PI);
	ray->ray_facing_left = !ray->ray_facing_right;
	ray->found_horz_hit = false;
	ray->found_vert_hit = false;
	ray->horz_wall_hit_x = 0;
	ray->horz_wall_hit_y = 0;
	ray->vert_wall_hit_x = 0;
	ray->vert_wall_hit_y = 0;
	ray->next_x = 0;
	ray->next_y = 0;
	ray->flg = -1;
	ray->is_door = false;
	return (ray);
}
