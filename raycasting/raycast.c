/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: captain <captain@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:31:49 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/21 17:14:58 by captain          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

t_ray	*create_Ray(double angle)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->ray_angle = normalize_angle(angle);
	ray->distance = 0;
	ray->wall_hit_X = 0;
	ray->wall_hit_Y = 0;
	ray->was_vert = false;
	ray->ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < M_PI;
	ray->ray_facing_up = !ray->ray_facing_down;
	ray->ray_facing_right = ray->ray_angle < 0.5 * M_PI || ray->ray_angle > (1.5 * M_PI);
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
	player = data->player;

	clear_image(player->ray);
	rays = malloc(sizeof(t_ray *) * WIN_WIDTH);
	ray_angle = player->rotation_angle - (player->FOV / 2);
	i = -1;
	while (++i < WIN_WIDTH)
	{
		t_ray	*ray;

		ray = create_Ray(ray_angle);
		cast_ray(ray, data);
		rays[i] = ray;
		ray_angle += player->FOV / WIN_WIDTH;
	}
	return (rays);
}

void	update_player_pos(t_data *data) {
	t_player	*player;

	player = data->player;
	int32_t new_X;
	int32_t new_Y;

	player->rotation_angle += player->turn_direction * player->rotation_speed;

	double	move_step = player->walk_direction * player->move_speed;
	if (player->walk)
	{
		player->side_angle = player->rotation_angle + (M_PI / 2);
		new_X = player->pl->instances->x + round(cos(player->side_angle) * move_step);
		new_Y = player->pl->instances->y + round(sin(player->side_angle) * move_step);
		player->walk = false;
	} else
	{
		new_X = player->pl->instances->x + round(cos(player->rotation_angle) * move_step);
		new_Y = player->pl->instances->y + round(sin(player->rotation_angle) * move_step);
	}
	if (!is_collision(data, new_X, new_Y)) {
		player->pl->instances->x = new_X;
		player->pl->instances->y = new_Y;
	}
}

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
    {
        data->player->vertical += (y - last_y) * 0.001;
        // if (data->player->vertical > M_PI / 2)
        //     data->player->vertical = M_PI / 2;
        // if (data->player->vertical < -M_PI / 2)
        //     data->player->vertical = -M_PI / 2;
    }
    
    // last_x = x;
    last_y = y;
	pos = x;
}

void	sprite_player(t_data *data)
{
	mlx_delete_image(data->map->mlx, data->player->gun);
	if (data->animation.current_frame == 0)
		data->player->gun = mlx_texture_to_image(data->map->mlx, data->player->txr1);
	else if (data->animation.current_frame == 1)
		data->player->gun = mlx_texture_to_image(data->map->mlx, data->player->txr2);
	else if (data->animation.current_frame == 2)
		data->player->gun = mlx_texture_to_image(data->map->mlx, data->player->txr3);
	else if (data->animation.current_frame == 3)
		data->player->gun = mlx_texture_to_image(data->map->mlx, data->player->txr4);
	else if (data->animation.current_frame == 4)
		data->player->gun = mlx_texture_to_image(data->map->mlx, data->player->txr1);
	mlx_image_to_window(data->map->mlx, data->player->gun, WIN_WIDTH / 2.5, WIN_HEIGHT - 300);
	mlx_resize_image(data->player->gun, 300, 300);
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
			if (data->animation.current_frame > 4)
			{
				data->animation.is_active = 0;
				data->animation.current_frame = 0;
			}
		}
	}
}

void	ft_right_left_arrow(t_data *data)
{
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_RIGHT))
		data->player->turn_direction = 1;
	else if (mlx_is_key_down(data->map->mlx, MLX_KEY_LEFT))
		data->player->turn_direction = -1;
	else
		data->player->turn_direction = 0;
	gun_animation(data);
	render_minimap(data);
	update_player_pos(data);
	mouse_handling(data);
	render_walls(cast_all_rays(data), data);
}

void	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->map->mlx);
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
	ft_right_left_arrow(data);
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
		// leaks !!!
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
	data->map->background = mlx_new_image(data->map->mlx, WIN_WIDTH, WIN_HEIGHT);
	bg_coloring(data->map->background, data->map);
	mlx_image_to_window(data->map->mlx, data->map->background, 0, 0);

	data->map->img = mlx_new_image(data->map->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(data->map->mlx, data->map->img, 0, 0);
	
	pl->pl = mlx_new_image(data->map->mlx, TILE_SIZE, TILE_SIZE);
	mlx_image_to_window(data->map->mlx, pl->pl, (pl->x + TILE_SIZE / 3), (pl->y + TILE_SIZE / 3));
	pl->ray = mlx_new_image(data->map->mlx, data->map->WIDHT, data->map->HEIGHT);
	mlx_image_to_window(data->map->mlx, pl->ray, 0, 0);
	load_textures(data);
	data->player->gun = mlx_texture_to_image(data->map->mlx, data->player->txr1);
	mlx_image_to_window(data->map->mlx, data->player->gun, WIN_WIDTH / 2.5, WIN_HEIGHT - 300);
	mlx_resize_image(data->player->gun, 300, 300);
	mlx_set_cursor_mode(data->map->mlx, MLX_MOUSE_DISABLED);
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
		write(STDERR_FILENO, "Failed to initialize MLX\n", 26);
		return (EXIT_FAILURE);
	}
	data->animation = (t_animation){.current_frame = 0, .is_active = 0, .frame_delay = 2, .frame_counter = 0};
	load_tex(data);
	init_imgs(data, pl);
	mlx_loop_hook(data->map->mlx, render, data);
	mlx_loop(data->map->mlx);
	mlx_terminate(data->map->mlx);
	return (EXIT_SUCCESS);
}
