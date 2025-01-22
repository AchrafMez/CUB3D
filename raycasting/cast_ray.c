/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:21:31 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/22 12:47:50 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

double	*_points_check(t_data *data, t_ray *ray, double x_step, double y_step)
{
	double	*points;

	points = malloc(sizeof(double) * 2);
	while (ray->next_x >= 0 && ray->next_x <= data->map->WIDHT
		&& ray->next_y >= 0 && ray->next_y <= data->map->HEIGHT)
	{
		if (is_wall(data, ray->next_x, ray->next_y))
		{
			if (ray->flg == 1)
				ray->found_horz_hit = true;
			else if (ray->flg == 0)
				ray->found_vert_hit = true;
			points[0] = ray->next_x;
			points[1] = ray->next_y;
			break ;
		}
		else
		{
			ray->next_x += x_step;
			ray->next_y += y_step;
		}
	}
	return (points);
}

void	ft_horizontal_interc(t_ray *ray, t_data *data)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	y_intercept = floor(data->player->pl->instances->y / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_down)
		y_intercept += TILE_SIZE;
	x_intercept = data->player->pl->instances->x + ((y_intercept
				- data->player->pl->instances->y) / tan(ray->ray_angle));
	y_step = TILE_SIZE;
	if (ray->ray_facing_up)
		y_step *= -1;
	x_step = y_step / tan(ray->ray_angle);
	if (ray->ray_facing_right && x_step < 0)
		x_step *= -1;
	if (ray->ray_facing_left && x_step > 0)
		x_step *= -1;
	ray->next_x = x_intercept;
	ray->next_y = y_intercept;
	if (ray->ray_facing_up)
		ray->next_y -= 0.001;
	ray->flg = 1;
	ray->horz_wall_hit_x = _points_check(data, ray, x_step, y_step)[0];
	ray->horz_wall_hit_y = _points_check(data, ray, x_step, y_step)[1];
}

void	ft_vertical_interc(t_ray *ray, t_data *data)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;

	x_intercept = floor(data->player->pl->instances->x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_right)
		x_intercept += TILE_SIZE;
	y_intercept = data->player->pl->instances->y + ((x_intercept
				- data->player->pl->instances->x) * tan(ray->ray_angle));
	x_step = TILE_SIZE;
	if (ray->ray_facing_left)
		x_step *= -1;
	y_step = x_step * tan(ray->ray_angle);
	if (ray->ray_facing_up && y_step > 0)
		y_step *= -1;
	if (ray->ray_facing_down && y_step < 0)
		y_step *= -1;
	ray->next_x = x_intercept;
	ray->next_y = y_intercept;
	if (ray->ray_facing_left)
		ray->next_x -= 0.001;
	ray->flg = 0;
	ray->vert_wall_hit_x = _points_check(data, ray, x_step, y_step)[0];
	ray->vert_wall_hit_y = _points_check(data, ray, x_step, y_step)[1];
}

void	_set_wall_hit(t_ray *ray, double horz_dis, double vert_dis)
{
	if (horz_dis < vert_dis)
	{
		ray->wall_hit_x = ray->horz_wall_hit_x;
		ray->wall_hit_y = ray->horz_wall_hit_y;
		ray->distance = horz_dis;
	}
	else
	{
		ray->wall_hit_x = ray->vert_wall_hit_x;
		ray->wall_hit_y = ray->vert_wall_hit_y;
		ray->distance = vert_dis;
		ray->was_vert = true;
	}
}

void	cast_ray(t_ray *ray, t_data *data)
{
	double	horz_hit_distance;
	double	vert_hit_distance;

	horz_hit_distance = DBL_MAX;
	vert_hit_distance = DBL_MAX;
	ft_horizontal_interc(ray, data);
	ft_vertical_interc(ray, data);
	if (ray->found_horz_hit == true)
	{
		horz_hit_distance = dst_2_pts(
				data->player->pl->instances->x,
				data->player->pl->instances->y,
				ray->horz_wall_hit_x, ray->horz_wall_hit_y);
	}
	if (ray->found_vert_hit == true)
	{
		vert_hit_distance = dst_2_pts(
				data->player->pl->instances->x,
				data->player->pl->instances->y,
				ray->vert_wall_hit_x, ray->vert_wall_hit_y);
	}
	_set_wall_hit(ray, horz_hit_distance, vert_hit_distance);
}
