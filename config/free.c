/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:09:11 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 05:47:29 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	free_fc(char **fc)
{
	int	i;

	i = 0;
	while (fc[i])
	{
		free(fc[i]);
		i++;
	}
	free(fc);
}

void	fre_maplines(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i] != NULL)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void	free_map(t_map *map)
{
	free((void *)map->no);
	free((void *)map->ea);
	free((void *)map->so);
	free((void *)map->we);
	free(map->floor_rgb);
	free(map->ciel_rgb);
	fre_maplines(map->map);
	free(map);
}

void	ft_exit(char *str, t_map *map)
{
	ft_putstr(str, 2);
	free_map(map);
	exit(EXIT_FAILURE);
}
