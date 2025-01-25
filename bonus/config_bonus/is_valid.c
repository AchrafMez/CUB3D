/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_valid.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:09:46 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:25:07 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

int	valide_color(char **fc, t_map *map)
{
	int	i;

	i = 0;
	while (fc[i])
	{
		if (check_color(fc[i], map) == 0)
		{
			if (ft_atoi(fc[i]) < 0 || ft_atoi(fc[i]) > 255)
				return (1);
		}
		else
			ft_exit("Error: Not a valid color\n", map);
		i++;
	}
	if (i != 3)
		ft_exit("Error: Not a valid color\n", map);
	return (0);
}

int	valid_color(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] < '0' || line[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	valid_map(char *line)
{
	while (*line == ' ' || *line == '\t' || *line == '\v')
		line++;
	if ((*line == 'S' && *(line + 1) == 'O') || (*line == 'W' && *(line
				+ 1) == 'E') || (*line == 'N' && *(line + 1) == 'O')
		|| (*line == 'E' && *(line + 1) == 'A'))
	{
		return (1);
	}
	if (*line == 'F' || *line == 'C')
	{
		return (1);
	}
	while (*line)
	{
		if (*line != ' ' && *line != '1' && *line != '0' && *line != 'N'
			&& *line != 'S' && *line != 'E' && *line != 'W' && *line != 'D')
		{
			return (0);
		}
		line++;
	}
	return (1);
}
