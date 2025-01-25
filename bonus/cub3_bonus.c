<<<<<<< HEAD:cub3.c
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/24 12:38:37 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/24 19:21:02 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"
=======
#include "cub3_bonus.h"
>>>>>>> main:bonus/cub3_bonus.c

void	leak(void)
{
	system("leaks cub3D");
}
<<<<<<< HEAD:cub3.c
=======

>>>>>>> main:bonus/cub3_bonus.c
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
