/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   FC.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:08:45 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 02:08:56 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	fill_floor(char **fc, t_map **map)
{
	int	i;

	i = 0;
	while (fc[i])
	{
		if ((*map)->floor_rgb[i] == -1)
			(*map)->floor_rgb[i] = ft_atoi(fc[i]);
		else if ((*map)->floor_rgb[i] != -1)
		{
			free_fc(fc);
			ft_exit("Error : Floor color already exist\n", *map);
		}
		i++;
	}
}

void	fill_ciel(char **fc, t_map **map)
{
	int	i;

	i = 0;
	while (fc[i])
	{
		if ((*map)->ciel_rgb[i] == -1)
			(*map)->ciel_rgb[i] = ft_atoi(fc[i]);
		else if ((*map)->ciel_rgb[i] != -1)
		{
			free_fc(fc);
			ft_exit("Error : Ciel color already exist\n", *map);
		}
		i++;
	}
}

void	store_fc(char **fc, int flag, t_map **map)
{
	if (flag == 0)
		fill_floor(fc, map);
	else if (flag == 1)
		fill_ciel(fc, map);
}

int	check_fc_prototype(char *line, t_map *map)
{
	unsigned long	i;
	int				comma;

	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
		i++;
	comma = 0;
	while (line[i])
	{
		if (line[i] == ',')
			comma++;
		if (isdigit(line[i]) == 0 && line[i] != ',' && line[i] != ' ')
			return (1);
		i++;
	}
	if (comma != 2)
		ft_exit("Error: Invalid color format\n", map);
	if (i == (strlen(line)))
		return (0);
	return (1);
}

void	fill_colors(char *line, t_map **map, int flag)
{
	char	**fc;

	fc = ft_split(line, ',');
	if (valide_color(fc, *map) == 0)
		store_fc(fc, flag, map);
	else
	{
		free_fc(fc);
		ft_exit("Error : Color not valid\n", *map);
	}
	free_fc(fc);
}
