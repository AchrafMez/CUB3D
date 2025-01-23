/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:31:49 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/23 11:52:51 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

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
	return (ray);
}

t_ray	**cast_all_rays(t_data *data)
{
	double		ray_angle;
	int			i;
	t_player	*player;
	t_ray		**rays;
	t_ray		*ray;

	player = data->player;
	rays = malloc(sizeof(t_ray *) * WIN_WIDTH);
	ray_angle = player->rotation_angle - (player->FOV / 2);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		ray = create_ray(ray_angle);
		cast_ray(ray, data);
		rays[i] = ray;
		ray_angle += player->FOV / WIN_WIDTH;
	}
	return (rays);
}

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
	pl->FOV = 60 * (M_PI / 180);
	pl->side_angle = 0.0;
	pl->x = data->map->player_x * TILE_SIZE;
	pl->y = data->map->player_y * TILE_SIZE;
	data->map->WIDHT *= TILE_SIZE;
	data->map->HEIGHT *= TILE_SIZE;
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
		WIN_WIDTH / 2.5, WIN_HEIGHT - 138 * 2);
	mlx_resize_image(data->player->gun, 91 * 2, 138 * 2);
	mlx_set_cursor_mode(data->map->mlx, MLX_MOUSE_DISABLED);
}

int	print_error(int err)
{
	if (err == 1)
		write(STDERR_FILENO, "Failed to initialize MLX\n", 26);
	return (EXIT_FAILURE);
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
		.frame_delay = 3, .frame_counter = 0, .move = 0};
	load_tex(data);
	init_imgs(data, pl);
	mlx_loop_hook(data->map->mlx, render, data);
	mlx_loop(data->map->mlx);
	mlx_terminate(data->map->mlx);
	return (EXIT_SUCCESS);
}
