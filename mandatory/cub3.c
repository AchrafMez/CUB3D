/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 06:05:10 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 11:53:24 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"

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
