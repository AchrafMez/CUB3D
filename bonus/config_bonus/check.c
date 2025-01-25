/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 01:46:37 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:25:35 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

int	check_color(char *fc, t_map *map)
{
	while ((*fc == ' ' || *fc == '\t'))
		fc++;
	if (*fc == '\0')
		ft_exit("Error: Empty RGB\n", map);
	while (ft_isdigit(*fc) != 0)
		fc++;
	while ((*fc == ' ' || *fc == '\t'))
		fc++;
	if (*fc != '\0')
		ft_exit("Error: Invalid Color format\n", map);
	return (0);
}

void	fexe(char *line, char *path)
{
	free(line);
	free(path);
	exit(EXIT_FAILURE);
}

int	check_positions(char *line, char f, char s, t_map **map)
{
	int		i;
	char	*path;

	i = 0;
	while (line[i])
	{
		if (line[i] == f && line[i + 1] == s)
		{
			i += 2;
			while (line[i] == ' ' || line[i] == '\t' || line[i] == '\v')
				i++;
			path = substring(line + i);
			if (check_texture_perm(path) == 0)
				store_textures(f, path, map);
			else
				fexe(line, path);
			free(path);
			return (0);
		}
		i++;
	}
	return (1);
}

int	check_identif(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if ((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' 
				&& line[i + 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E')
			|| (line[i] == 'E' && line[i + 1] == 'A'))
			return (0);
		else if (line[i] == 'F' || line[i] == 'C')
			return (0);
		i++;
	}
	return (1);
}

int	check(char *line, t_map **map)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 'N' && line[i + 1] == 'O')
			check_positions(line, 'N', 'O', map);
		else if (line[i] == 'S' && line[i + 1] == 'O')
			check_positions(line, 'S', 'O', map);
		else if (line[i] == 'W' && line[i + 1] == 'E')
			check_positions(line, 'W', 'E', map);
		else if (line[i] == 'E' && line[i + 1] == 'A')
			check_positions(line, 'E', 'A', map);
		else if ((line[i] == 'F' && line[i + 1] == ' ') || (line[i] == 'C' && 
				line[i + 1] == ' '))
		{
			if (check_fc(line, *map) == 0)
				parse_colors(line, map);
		}
		else
			return (1);
		i++;
	}
	return (0);
}
