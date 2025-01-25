/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 03:06:13 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:25:03 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	parse_colors(char *line, t_map **map)
{
	char	*floor;

	while (*line && (*line == ' ' || *line == '\t' || *line == '\v'))
		line++;
	if (*line == 'F')
	{
		line++;
		floor = substring(line);
		fill_colors(floor, map, 0);
		free(floor);
	}
	else if (*line == 'C')
	{
		line++;
		floor = substring(line);
		fill_colors(floor, map, 1);
		free(floor);
	}
}

int	is_map(char *line)
{
	int	i;

	i = 0;
	if (!line)
		return (0);
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t' && line[i] != '1'
			&& line[i] != '0' && line[i] != 'W' && line[i] != 'E'
			&& line[i] != 'S' && line[i] != 'N' && line[i] != 'D')
			return (1);
		i++;
	}
	return (0);
}

int	get_map_width(char **map)
{
	int	i;
	int	width;
	int	current;

	i = -1;
	width = 0;
	current = 0;
	while (map[++i])
	{
		current = ft_strlen(map[i]);
		if (current > width)
			width = current;
	}
	return (width);
}

void	whxy(t_map **map)
{
	int	i;
	int	j;

	i = -1;
	while ((*map)->map[++i])
	{
		j = -1;
		while ((*map)->map[i][++j])
		{
			if ((*map)->map[i][j] == 'S' || (*map)->map[i][j] == 'W'
				|| (*map)->map[i][j] == 'E' || (*map)->map[i][j] == 'N')
			{
				(*map)->player = (*map)->map[i][j];
				(*map)->player_y = i;
				(*map)->player_x = j;
			}
		}
	}
	(*map)->height = i;
	(*map)->width = get_map_width((*map)->map);
}
