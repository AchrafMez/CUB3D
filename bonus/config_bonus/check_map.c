/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:46:05 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:25:33 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	check_filled_map(t_map *map)
{
	if (!map->map || map->ciel_rgb[0] == -1 || map->floor_rgb[0] == -1
		|| !map->ea || !map->no || !map->so || !map->we)
		ft_exit("Error: Map not filled correctly!\n", map);
}

void	check_ones(char *line, t_map *map)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			ft_exit("Error: Invalid character in the first or last line", map);
		line++;
	}
}

void	check_map_last_char(t_map *map, int i)
{
	int	end;

	end = 0;
	check_ones(map->map[0], map);
	end = ft_strlen(map->map[i]) - 1;
	if (map->map[i][end] != '1' && map->map[i][end] != ' ')
		ft_exit("Error: Last character in the map\n", map);
}

void	check_map_char(t_map *map, int i, int *player_count)
{
	int	j;

	j = 0;
	while (map->map[i][j] == ' ' || map->map[i][j] == '\t')
		j++;
	if (map->map[i][j] != '1')
		ft_exit("Error: first character in the map\n", map);
	while (map->map[i][j])
	{
		if (map->map[i][j] != '1' && map->map[i][j] != '0'
			&& map->map[i][j] != ' ' && map->map[i][j] != 'N'
			&& map->map[i][j] != 'S' && map->map[i][j] != 'W'
			&& map->map[i][j] != 'E' && map->map[i][j] != 'D')
			ft_exit("Error: Unexpected character in the map!\n", map);
		if (map->map[i][j] == 'S' || map->map[i][j] == 'N'
			|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			(*player_count)++;
		j++;
	}
}

void	check_zeros(t_map *map, int i, int j)
{
	if (map->map[i][j + 1] == ' ' || map->map[i][j - 1] == ' ')
		ft_exit("Error: an area inside the map must be closed\n", map);
	if (ft_strlen(map->map[i - 1]) <= j || ft_strlen(map->map[i + 1]) <= j
		|| map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ')
		ft_exit("Error: an area inside the map must be closed\n", map);
}
