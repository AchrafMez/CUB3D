/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:09:06 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/26 17:02:28 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

void	_run(t_map *map, char **av)
{
	null_init(map);
	read_map(av[1], &map);
	check_filled_map(map);
	check_map_chars(map);
	whxy(&map);
	check_map_spaces(map);
	is_valid_door(map);
}

int	main(int ac, char **av)
{
	t_data	data;
	t_map	*map;

	if (ac == 2)
	{
		if (check_extension(av[1]))
		{
			map = malloc(sizeof(t_map));
			if (!map)
				return (free_map(map), EXIT_FAILURE);
			data.map = map;
			_run(map, av);
			if (raycast(&data))
				return (free_map(map), EXIT_FAILURE);
			free_map(map);
		}
		else
			printf("Uncorrect filename\n");
	}
	else
		printf("Usage: cub3D *.cub\n");
	return (0);
}
