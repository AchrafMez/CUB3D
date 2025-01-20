/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_ray.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/15 19:21:31 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/20 10:45:34 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

double	*ft_horizontal(t_ray *ray, t_data *data)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	next_horz_X;
	double	next_horz_Y;
	double	horz_wall_hit_X;
	double	horz_wall_hit_Y;
	double	*horz_cord;

	horz_wall_hit_X = 0;
	horz_wall_hit_Y = 0;
	horz_cord = malloc(sizeof(int *) * 2);
	y_intercept = floor(data->player->pl->instances->y / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_down)
		y_intercept += TILE_SIZE;
	x_intercept = data->player->pl->instances->x + ((y_intercept - data->player->pl->instances->y) / tan(ray->ray_angle));

	y_step = TILE_SIZE;
	if (ray->ray_facing_up)
		y_step *= -1;
	x_step = y_step / tan(ray->ray_angle);
	if (ray->ray_facing_right && x_step < 0)
		x_step *= -1;
	if (ray->ray_facing_left && x_step > 0)
		x_step *= -1;
	next_horz_X = x_intercept;
	next_horz_Y = y_intercept;
	if (ray->ray_facing_up)
		next_horz_Y -= 0.001;
	while (next_horz_X >= 0 && next_horz_X <= data->map->WIDHT
		&& next_horz_Y >= 0 && next_horz_Y <= data->map->HEIGHT)
	{
		if (is_WALL(data, next_horz_X, next_horz_Y))
		{
			ray->found_horz_hit = true;
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
	horz_cord[0] = horz_wall_hit_X;
	horz_cord[1] = horz_wall_hit_Y;
	return (horz_cord);
}

double	*ft_vertical(t_ray *ray, t_data *data)
{
	double	x_intercept;
	double	y_intercept;
	double	x_step;
	double	y_step;
	double	next_vert_X;
	double	next_vert_Y;
	double	vert_wall_hit_X;
	double	vert_wall_hit_Y;
	double	*vert_cord;

	vert_wall_hit_X = 0;
	vert_wall_hit_Y = 0;
	vert_cord = malloc(sizeof(int *) * 2);
	x_intercept = floor(data->player->pl->instances->x / TILE_SIZE) * TILE_SIZE;
	if (ray->ray_facing_right)
		x_intercept += TILE_SIZE;
	y_intercept = data->player->pl->instances->y + ((x_intercept - data->player->pl->instances->x) * tan(ray->ray_angle));
	x_step = TILE_SIZE;
	if (ray->ray_facing_left)
		x_step *= -1;
	y_step = x_step * tan(ray->ray_angle);
	if (ray->ray_facing_up && y_step > 0)
		y_step *= -1;
	if (ray->ray_facing_down && y_step < 0)
		y_step *= -1;
	next_vert_X = x_intercept;
	next_vert_Y = y_intercept;
	if (ray->ray_facing_left)
		next_vert_X -= 0.001;
	while (next_vert_X >= 0 && next_vert_X <= data->map->WIDHT
		&& next_vert_Y >= 0 && next_vert_Y <= data->map->HEIGHT)
	{
		if (is_WALL(data, next_vert_X, next_vert_Y))
		{
			ray->found_vert_hit = true;
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
	vert_cord[0] = vert_wall_hit_X;
	vert_cord[1] = vert_wall_hit_Y;
	return (vert_cord);
}

void	cast_ray(t_ray *ray, t_data *data)
{
	double	horz_hit_distance = DBL_MAX;
	double	vert_hit_distance = DBL_MAX;
	double	*ret_horz = ft_horizontal(ray, data);
	double	*ret_vert = ft_vertical(ray, data);

	if (ray->found_horz_hit == true)
		horz_hit_distance = distance_between_2_points(data->player->pl->instances->x,
			data->player->pl->instances->y, ret_horz[0], ret_horz[1]);
	if (ray->found_vert_hit == true)
		vert_hit_distance = distance_between_2_points(data->player->pl->instances->x,
			data->player->pl->instances->y, ret_vert[0], ret_vert[1]);
	if (horz_hit_distance < vert_hit_distance)
	{
		ray->wall_hit_X = ret_horz[0];
		ray->wall_hit_Y = ret_horz[1];
		ray->distance = horz_hit_distance;
	}
	else
	{
		ray->wall_hit_X = ret_vert[0];
		ray->wall_hit_Y = ret_vert[1];
		ray->distance = vert_hit_distance;
		ray->was_vert = true;
	}
	// render_rays(data, ray->wall_hit_X, ray->wall_hit_Y);
}
