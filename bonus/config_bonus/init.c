/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:09:36 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:25:09 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	null_init(t_map *map)
{
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->map = NULL;
	map->player_x = 0;
	map->player_y = 0;
	init_ciel(&map);
	init_floor(&map);
}

void	init_floor(t_map **map)
{
	(*map)->floor_rgb = malloc(sizeof(int) * 3);
	if (!(*map)->floor_rgb)
		return ;
	(*map)->floor_rgb[0] = -1;
	(*map)->floor_rgb[1] = -1;
	(*map)->floor_rgb[2] = -1;
}

void	init_ciel(t_map **map)
{
	(*map)->ciel_rgb = malloc(sizeof(int) * 3);
	if (!(*map)->ciel_rgb)
		return ;
	(*map)->ciel_rgb[0] = -1;
	(*map)->ciel_rgb[1] = -1;
	(*map)->ciel_rgb[2] = -1;
}
