/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:31:49 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/12 15:41:36 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void render_map(t_map *map)
{
	int	y;
	int	x;
	int	py;
	int	px;

	y = -1;
	while (map->map[++y] != NULL)
	{
		x = -1;
		while (map->map[y][++x])
		{
			uint32_t color = COLOR_WALL; // Default to wall
			if (map->map[y][x] == '1')
				color = COLOR_SPACE;
			else if (map->map[y][x] == ' ')
				color = 0x00000000;
			py = -1;
			while (++py < TILE_SIZE)
			{
				px = -1;
				while (++px < TILE_SIZE)
					mlx_put_pixel(map->mini_map, (x * TILE_SIZE + px) * MINIMAP_SCALE_FACTOR, (y * TILE_SIZE + py) * MINIMAP_SCALE_FACTOR, color);
			}
		}
	}
}

int	is_WALL(t_data *data, int x, int y)
{
	int	X_index;
	int	Y_index;

	if (x < 0 || x >= data->map->WIDHT || y < 0 || y >= data->map->HEIGHT)
		return (1);
	Y_index = round(y / TILE_SIZE);
	X_index = round(x / TILE_SIZE);
	if (data->map->map[Y_index][X_index] == '1')
		return (1);
	return (0);
}

void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color) {
	int dx;
	int dy;
	int	i;

	dx = x1- x0;
	dy = y1 - y0;
	i = -1;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float x_inc = dx / (float)steps;
	float y_inc = dy / (float)steps;

	float x = x0;
	float y = y0;
	while (++i <= steps)
	{
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			mlx_put_pixel(img, (int)round(x), (int)round(y), color);
		x += x_inc;
		y += y_inc;
	}
}

float	normalize_angle(float angle)
{
	float	ret;

	ret = remainder(angle, (2 * PI));
	if (ret < 0)
		ret += (2 * PI);
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

void	render_rays(t_data *data, float x1, float y1)
{
	draw_line(data->player->ray, data->player->pl->instances->x * MINIMAP_SCALE_FACTOR,
		data->player->pl->instances->y * MINIMAP_SCALE_FACTOR,
		x1 * MINIMAP_SCALE_FACTOR, y1 * MINIMAP_SCALE_FACTOR, MAIN_COLOR);
}

double	distance_between_2_points(int32_t x1, int32_t y1, float x2, float y2)
{
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void	cast_rays(t_ray *ray, t_data *data)
{
	float	x_intercept;
	float	y_intercept;
	float	x_step;
	float	y_step;
	float	next_horz_X;
	float	next_horz_Y;
	bool	found_horz_hit;
	float	horz_wall_hit_X;
	float	horz_wall_hit_Y;

	//////////////////////////////////////////////
	/// HORIZONTAL RAY-GRID INTERSECTION CODE  ///   
	//////////////////////////////////////////////

	found_horz_hit = false;
	horz_wall_hit_X = 0;
	horz_wall_hit_Y = 0;

	// find the Y coordinate of the closest horizontal grid intersection
	y_intercept = floor(data->player->pl->instances->y / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_down)
		y_intercept += TILE_SIZE;
	// find the X coordinate of the closest horizontal grid intersection
	x_intercept = data->player->pl->instances->x + ((y_intercept - data->player->pl->instances->y) / tan(ray->ray_angle));

	// Calculate the Ystep
	y_step = TILE_SIZE;
	if (ray->ray_facing_up)
		y_step *= -1;
	// Calculate the Xstep
	x_step = y_step / tan(ray->ray_angle);
	if (ray->ray_facing_right && x_step < 0)
		x_step *= -1;
	if (ray->ray_facing_left && x_step > 0)
		x_step *= -1;

	next_horz_X = x_intercept;
	next_horz_Y = y_intercept;

	while (next_horz_X >= 0 && next_horz_X <= data->map->WIDHT
		&& next_horz_Y >= 0 && next_horz_Y <= data->map->HEIGHT)
	{
		if (is_WALL(data, next_horz_X, next_horz_Y - (ray->ray_facing_up ? 1 : 0)))
		{
			found_horz_hit = true;
			horz_wall_hit_X = next_horz_X;
			horz_wall_hit_Y = next_horz_Y;
			break ;
		}
		else
		{
			next_horz_X += x_step;
			next_horz_Y += y_step;
		}
	}
	//////////////////////////////////////////////
	///  VERTICAL RAY-GRID INTERSECTION CODE   ///   
	//////////////////////////////////////////////
	
	float	next_vert_X;
	float	next_vert_Y;
	bool	found_vert_hit;
	float	vert_wall_hit_X;
	float	vert_wall_hit_Y;
	
	found_vert_hit = false;
	vert_wall_hit_X = 0;
	vert_wall_hit_Y = 0;

	// find the X coordinate of the closest vertical grid intersection
	x_intercept = floor(data->player->pl->instances->x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_right)
		x_intercept += TILE_SIZE;
	// find the Y coordinate of the closest vertical grid intersection
	y_intercept = data->player->pl->instances->y + ((x_intercept - data->player->pl->instances->x) * tan(ray->ray_angle));

	// Calculate the Ystep
	x_step = TILE_SIZE;
	if (ray->ray_facing_left)
		x_step *= -1;
	// Calculate the Xstep
	y_step = x_step * tan(ray->ray_angle);
	if (ray->ray_facing_up && y_step > 0)
		y_step *= -1;
	if (ray->ray_facing_down && y_step < 0)
		y_step *= -1;

	next_vert_X = x_intercept;
	next_vert_Y = y_intercept;

	while (next_vert_X >= 0 && next_vert_X <= data->map->WIDHT && next_vert_Y >= 0 && next_vert_Y <= data->map->HEIGHT)
	{
		if (is_WALL(data, next_vert_X - (ray->ray_facing_left ? 1 : 0), next_vert_Y))
		{
			found_vert_hit = true;
			vert_wall_hit_X = next_vert_X;
			vert_wall_hit_Y = next_vert_Y;
			break ;
		}
		else
		{
			next_vert_X += x_step;
			next_vert_Y += y_step;
		}
	}

	// Calculate the distance to get the smallest point
	double	horz_hit_distance = DBL_MAX;
	double	vert_hit_distance = DBL_MAX;
	if (found_horz_hit == true)
		horz_hit_distance = distance_between_2_points(data->player->pl->instances->x,
			data->player->pl->instances->y, horz_wall_hit_X, horz_wall_hit_Y);
	if (found_vert_hit == true)
		vert_hit_distance = distance_between_2_points(data->player->pl->instances->x,
			data->player->pl->instances->y, vert_wall_hit_X, vert_wall_hit_Y);
	if (horz_hit_distance < vert_hit_distance)
	{
		ray->wall_hit_X = horz_wall_hit_X;
		ray->wall_hit_Y = horz_wall_hit_Y;
		ray->distance = horz_hit_distance;
	}
	else
	{
		ray->wall_hit_X = vert_wall_hit_X;
		ray->wall_hit_Y = vert_wall_hit_Y;
		ray->distance = vert_hit_distance;
	}
	render_rays(data, ray->wall_hit_X, ray->wall_hit_Y);
}

t_ray	*create_Ray(float angle)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	ray->ray_angle = normalize_angle(angle);
	ray->distance = 0;
	ray->wall_hit_X = 0;
	ray->wall_hit_Y = 0;
	ray->ray_facing_down = ray->ray_angle > 0 && ray->ray_angle < PI;
	ray->ray_facing_up = !ray->ray_facing_down;

	ray->ray_facing_right = ray->ray_angle < 0.5 * PI || ray->ray_angle > (1.5 * PI);
	ray->ray_facing_left = !ray->ray_facing_right;

	return (ray);
}

t_ray	**cast_all_rays(t_data *data)
{
	int		columnId;
	float	ray_angle;
	int		i;
	int		rays_num;
	t_map	*game;

	game = data->map;
	rays_num = game->WIDHT;
	t_ray	**rays;

	clear_image(data->player->ray);
	rays = malloc(sizeof(t_ray *) * rays_num);
	columnId = 0;
	ray_angle = data->player->rotation_angle - (data->player->FOV / 2);
	i = -1;
	while (++i < rays_num)
	{
		t_ray	*ray;

		ray = create_Ray(ray_angle);
		cast_rays(ray, data);
		rays[i] = ray;
		ray_angle += data->player->FOV / rays_num;
		columnId++;
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
			if (x + j >= 0 && (uint32_t)(x + j) < img->width && (uint32_t)(y + i) >= 0 && (uint32_t)(y + i) < img->height)
            {
                mlx_put_pixel(img, x + j, y + i, color);
            }
			j++;
		}
		i++;
	}
}

void	render_3d_projection_walls(t_ray **rays, t_data *data)
{
	int		i;
	int		rays_num;
	t_ray	*ray;
	int		wall_strip_height;
	float	correct_ray_dist;
	float	distance_projection_plane;

	i = -1;
	clear_image(data->map->img);
	rays_num = data->map->WIDHT;
	while (++i < rays_num)
	{
		ray = rays[i];
		correct_ray_dist = ray->distance * cos(ray->ray_angle - data->player->rotation_angle);
		distance_projection_plane = (data->map->WIDHT / 2) / tan(data->player->FOV / 2);
		wall_strip_height = (TILE_SIZE / correct_ray_dist) * distance_projection_plane;
		draw_rectangle(data->map->img, i * WALL_STRIP_WIDTH,
						(data->map->HEIGHT / 2) - (wall_strip_height / 2),
						WALL_STRIP_WIDTH,
						wall_strip_height,
						MAIN_COLOR);
	}
}

int	is_collision(t_data *data, float new_X, float new_Y)
{
	if (is_WALL(data, new_X - TILE_SIZE / 4, new_Y - TILE_SIZE / 4) ||
		is_WALL(data, new_X + TILE_SIZE / 4, new_Y - TILE_SIZE / 4) ||
		is_WALL(data, new_X - TILE_SIZE / 4, new_Y + TILE_SIZE / 4) ||
		is_WALL(data, new_X + TILE_SIZE / 4, new_Y + TILE_SIZE / 4))
		return (1);
	return (0);
}

void	update_player(t_data *data) {
	t_player	*player;

	player = data->player;
	int32_t new_X;
	int32_t new_Y;

	player->rotation_angle += player->turn_direction * player->rotation_speed;

	float move_step = player->walk_direction * player->move_speed;
	new_X = player->pl->instances->x + round(cos(player->rotation_angle) * move_step);
	new_Y = player->pl->instances->y + round(sin(player->rotation_angle) * move_step);
	if (!is_collision(data, new_X, new_Y)) {
		player->pl->instances->x = new_X;
		player->pl->instances->y = new_Y;
	}
}

void	render(void *param)
{
	t_data	*data;
	t_ray	**rays;

	data = (t_data *)param;
	
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(data->map->mlx);
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_UP))
		data->player->walk_direction = 1;
	else if (mlx_is_key_down(data->map->mlx, MLX_KEY_DOWN))
		data->player->walk_direction = -1;
	else
		data->player->walk_direction = 0;
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_RIGHT))
		data->player->turn_direction = 1;
	else if (mlx_is_key_down(data->map->mlx, MLX_KEY_LEFT))
		data->player->turn_direction = -1;
	else
		data->player->turn_direction = 0;
	update_player(data);
	rays = cast_all_rays(data);
	render_3d_projection_walls(rays, data);
}

void	player_init(t_player *pl, t_data *data)
{
	pl->walk_direction = 0;
	pl->turn_direction = 0;
	pl->rotation_angle = PI / 2;
	pl->move_speed = 2.0;
	pl->rotation_speed = 2 * (PI / 180);
	pl->FOV = 60 * (PI / 180);
	pl->x = data->map->player_x * TILE_SIZE;
	pl->y = data->map->player_y * TILE_SIZE;
}

int	raycast(t_data *data)
{
	t_player	*pl;

	pl = (t_player *)malloc(sizeof(t_player));
	player_init(pl, data);
	data->player = pl;
	data->map->WIDHT *= TILE_SIZE;
	data->map->HEIGHT *= TILE_SIZE;
	data->map->mlx = mlx_init(data->map->WIDHT, data->map->HEIGHT, "cub3D", true);
	if (!data->map->mlx) {
		fprintf(stderr, "Failed to initialize MLX\n");
		return EXIT_FAILURE;
	}

	data->map->mini_map = mlx_new_image(data->map->mlx, data->map->WIDHT * WALL_STRIP_WIDTH, data->map->HEIGHT * WALL_STRIP_WIDTH);
	pl->pl = mlx_new_image(data->map->mlx, TILE_SIZE, TILE_SIZE);
	data->map->img = mlx_new_image(data->map->mlx, data->map->WIDHT, data->map->HEIGHT);
	mlx_image_to_window(data->map->mlx, data->map->mini_map, 0, 0);
	mlx_image_to_window(data->map->mlx, data->map->img, 0, 0);
	render_map(data->map);
	mlx_image_to_window(data->map->mlx, pl->pl, (pl->x + TILE_SIZE / 3), (pl->y + TILE_SIZE / 3));
	pl->ray = mlx_new_image(data->map->mlx, data->map->WIDHT, data->map->HEIGHT);
	mlx_image_to_window(data->map->mlx, pl->ray, 0, 0);

	mlx_loop_hook(data->map->mlx, render, data);
	mlx_loop(data->map->mlx);
	mlx_delete_image(data->map->mlx, data->map->mini_map);
	mlx_terminate(data->map->mlx);
	return EXIT_SUCCESS;
}
