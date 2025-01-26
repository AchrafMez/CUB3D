/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:45:02 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/26 10:22:02 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

int	check_extension(char *file_name)
{
	const char	extension[5] = ".cub";
	int			check_counter;
	int			file_counter;

	check_counter = 3;
	file_counter = ft_strlen(file_name) - 1;
	while (check_counter >= 0 && extension[check_counter])
	{
		if (file_name[file_counter--] != extension[check_counter--])
			return (0);
	}
	return (1);
}

void	check_map_spaces(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			if (map->map[i][j] == '0' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'W')
				check_zeros(map, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}

int	check_map_chars(t_map *map)
{
	int	i;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map->map[i])
	{
		check_map_last_char(map, i);
		check_map_char(map, i, &player_count);
		i++;
	}
	if (player_count != 1)
		ft_exit("Error: The map needs one player\n", map);
	check_ones(map->map[i - 1], map);
	return (0);
}

int	check_fc(char *line, t_map *map)
{
	int	i;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
		i++;
	if (((line[i] == 'F' && line[i + 1] != '\t') 
			&& (line[i] == 'F' && line[i + 1] != ' ')) 
		|| ((line[i] == 'C' && line[i + 1] != '\t')
			&& (line[i] == 'C' && line[i + 1] != ' ')))
		ft_exit("Error: F or C Not filled as expected\n", map);
	if ((line[i] == 'F' && (line[i + 1] == ' ' || line[i + 1] == '\t'))
		|| (line[i] == 'C' && (line[i + 1] == ' ' || line[i + 1] == '\t')))
	{
		i++;
		if (check_fc_prototype(line + i, map) == 0)
			return (0);
	}
	return (1);
}

void	is_valid_door(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'D')
			{
				if (map->map[i][j + 1] == ' ' || map->map[i][j - 1] == ' '
					|| map->map[i + 1][j] == ' ' || map->map[i - 1][j] == ' ')
					ft_exit("Error: Not a valid door!\n", map);
			}
			j++;
		}
		i++;
	}
}