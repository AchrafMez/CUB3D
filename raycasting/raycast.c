/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:31:49 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/16 18:14:41 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

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

void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color)
{
	int dx;
	int dy;
	int	i;

	dx = x1- x0;
	dy = y1 - y0;
	i = -1;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	double x_inc = dx / (double)steps;
	double y_inc = dy / (double)steps;

	double x = x0;
	double y = y0;
	while (++i <= steps)
	{
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			mlx_put_pixel(img, (int)round(x), (int)round(y), color);
		x += x_inc;
		y += y_inc;
	}
}

double	normalize_angle(double angle)
{
	double	ret;

	ret = remainder(angle, (2 * M_PI));
	if (ret < 0)
		ret += (2 * M_PI);
	return (ret);
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

double	distance_between_2_points(int32_t x1, int32_t y1, double x2, double y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

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

	return (ray);
}

t_ray	**cast_all_rays(t_data *data)
{
	double		ray_angle;
	int			i;
	t_player	*player;
	t_ray	**rays;
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

void	draw_rectangle(mlx_image_t *img, int x, int y, int width, int height, uint32_t color)
{
	int	i;
	int	j;

	i = 0;
	while (i < height)
	{
		j = 0;
		while (j < width)
		{
			if (x + j >= 0 && (uint32_t)(x + j) < img->width
				&& (uint32_t)(y + i) >= 0 && (uint32_t)(y + i) < img->height)
                mlx_put_pixel(img, x + j, y + i, color);
			j++;
		}
		i++;
	}
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

	x = 0;
	y = 0;
	mlx_get_mouse_pos(data->map->mlx, &x, &y);
	if (pos != 0)
		data->player->rotation_angle += (x - pos) * 0.001;
	pos = x;
}

void	render(void *param)
{
	// static int	mouse_pos;
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
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_RIGHT))
		data->player->turn_direction = 1;
	else if (mlx_is_key_down(data->map->mlx, MLX_KEY_LEFT))
		data->player->turn_direction = -1;
	else
		data->player->turn_direction = 0;
	update_player_pos(data);
	render_3d_projection_walls(cast_all_rays(data), data);
	mouse_handling(data);
}

void	player_init(t_player *pl, t_data *data)
{
	pl->walk_direction = 0;
	pl->turn_direction = 0;
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
	pl->FOV = 60.0 * (M_PI / 180.0);
	pl->side_angle = 0.0;
	pl->x = data->map->player_x * TILE_SIZE;
	pl->y = data->map->player_y * TILE_SIZE;
	data->map->WIDHT *= TILE_SIZE;
	data->map->HEIGHT *= TILE_SIZE;
}

uint32_t	get_rgb(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

void	color_background(mlx_image_t *bg, t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while ((uint32_t)(++y) < bg->height / 2)
	{
		x = -1;
		while ((uint32_t)++x < bg->width)
			mlx_put_pixel(bg, x, y, get_rgb(map->ciel_rgb[0], map->ciel_rgb[1], map->ciel_rgb[2]));
	}
	y = bg->height / 2;
	while ((uint32_t)++y < bg->height)
	{
		x = -1;
		while ((uint32_t)++x < bg->width)
			mlx_put_pixel(bg, x, y, get_rgb(map->floor_rgb[0], map->floor_rgb[1], map->floor_rgb[2]));
	}
}

void	init_imgs(t_data *data, t_player *pl)
{
	data->map->background = mlx_new_image(data->map->mlx, WIN_WIDTH, WIN_HEIGHT);
	color_background(data->map->background, data->map);
	mlx_image_to_window(data->map->mlx, data->map->background, 0, 0);

	data->map->img = mlx_new_image(data->map->mlx, WIN_WIDTH, WIN_HEIGHT);
	mlx_image_to_window(data->map->mlx, data->map->img, 0, 0);

	data->map->mini_map = mlx_new_image(data->map->mlx, data->map->WIDHT, data->map->HEIGHT);
	mlx_image_to_window(data->map->mlx, data->map->mini_map, 0, 0);
	
	pl->pl = mlx_new_image(data->map->mlx, TILE_SIZE, TILE_SIZE);
	mlx_image_to_window(data->map->mlx, pl->pl, (pl->x + TILE_SIZE / 3), (pl->y + TILE_SIZE / 3));
	mlx_set_cursor_mode(data->map->mlx, MLX_MOUSE_DISABLED);
}

int	raycast(t_data *data)
{
	t_player	*pl;

	pl = (t_player *)malloc(sizeof(t_player));
	player_init(pl, data);
	data->player = pl;

	data->map->mlx = mlx_init(WIN_WIDTH, WIN_HEIGHT, "cub3D", true);
	if (!data->map->mlx) {
		write(STDERR_FILENO, "Failed to initialize MLX\n", 35);
		return (EXIT_FAILURE);
	}
	init_imgs(data, pl);
	render_map(data->map);
	pl->ray = mlx_new_image(data->map->mlx, data->map->WIDHT, data->map->HEIGHT);
	mlx_image_to_window(data->map->mlx, pl->ray, 0, 0);

	mlx_loop_hook(data->map->mlx, render, data);
	mlx_loop(data->map->mlx);
	// mlx_delete_image(data->map->mlx, data->map->mini_map);
	mlx_terminate(data->map->mlx);
	return (EXIT_SUCCESS);
}
