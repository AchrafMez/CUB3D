/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 09:09:06 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/26 10:23:28 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3_bonus.h"

void	leak(void)
{
	system("leaks cub3D");
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
			null_init(map);
			read_map(av[1], &map);
			check_filled_map(map);
			check_map_chars(map);
			whxy(&map);
			check_map_spaces(map);
			is_valid_door(map);
			data.map = map;
			if (raycast(&data))
				return (free_map(map), EXIT_FAILURE);
			free_map(map);
		}
		else
			printf("Uncorrect filename\n");
		// atexit(leak);
	}
	else
		printf("Usage: cub3D *.cub\n");
	return (0);
}
