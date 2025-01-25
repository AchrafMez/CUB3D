/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:09:36 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 02:09:37 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	null_init(t_map *map)
{
	map->NO = NULL;
	map->SO = NULL;
	map->WE = NULL;
	map->EA = NULL;
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
