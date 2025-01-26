/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doors.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 13:06:34 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/26 13:11:06 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	toggle_door(t_data *data, int x, int y)
{
	double	dist;

	dist = sqrt(pow(data->player->pl->instances->x - (x * TILE_SIZE), 2) + 
			pow(data->player->pl->instances->y - (y * TILE_SIZE), 2));
	if (dist <= TILE_SIZE * 2)
	{
		if (data->map->map[y][x] == 'D')
			data->map->map[y][x] = 'O';
		else if (data->map->map[y][x] == 'O')
			data->map->map[y][x] = 'D';
	}
}

void	check_door(t_data *data, int adjacent_offset[4][2],
					int player_map_x, int player_map_y)
{
	int	i;
	int	door_x;
	int	door_y;

	i = 0;
	while (i < 4)
	{
		door_x = player_map_x + adjacent_offset[i][0];
		door_y = player_map_y + adjacent_offset[i][1];
		if (data->map->map[door_y][door_x] == 'D' || 
			data->map->map[door_y][door_x] == 'O')
		{
			toggle_door(data, door_x, door_y);
			break ;
		}
		i++;
	}
}

void	handle_door_interaction(t_data *data)
{
	int	player_map_x;
	int	player_map_y;
	int	check_offsets[4][2];

	player_map_x = (int)(data->player->pl->instances->x / TILE_SIZE);
	player_map_y = (int)(data->player->pl->instances->y / TILE_SIZE);
	check_offsets[0][0] = 0;
	check_offsets[0][1] = 1;
	check_offsets[1][0] = 0;
	check_offsets[1][1] = -1;
	check_offsets[2][0] = 1;
	check_offsets[2][1] = 0;
	check_offsets[3][0] = -1;
	check_offsets[3][1] = 0;
	check_door(data, check_offsets, player_map_x, player_map_y);
}
