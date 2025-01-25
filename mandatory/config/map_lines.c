/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:09:56 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 02:57:27 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

int	lines_count_checker(char *trimmed_line, int map_started, char *line)
{
	if (*trimmed_line == '\0' && map_started == 0)
	{
		free(line);
		return (0);
	}
	else if (*trimmed_line == '\0' && map_started == 1)
	{
		free(line);
		return (0);
	}
	return (1);
}

void	map_lines_exit(char *str, char *line, t_map *map)
{
	free(line);
	free_map(map);
	ft_putstr(str, 2);
	exit(EXIT_FAILURE);
}

int	lines_count(int fd, t_map *map)
{
	char		*line;
	int			map_started;
	static int	count;
	char		*trimmed_line;

	map_started = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		trimmed_line = skip_whiespaces(line);
		if (lines_count_checker(trimmed_line, map_started, line) == 0)
			continue ;
		else if (is_map(trimmed_line) == 0)
		{
			map_started = 1;
			count++;
		}
		else if (map_started == 1)
			map_lines_exit("Error: Invalid line inside the map\n", line, map);
		free(line);
	}
	return (count);
}

void	process_line(char *line, t_map *map, int *map_started, int *inside)
{
	char	*trimmed_line;

	trimmed_line = skip_whiespaces(line);
	if (valid_map(trimmed_line) == 0)
		map_lines_exit("Error: Invalid character inside the map\n", line, map);
	if (is_map(trimmed_line) == 0)
	{
		if (*trimmed_line == '\0')
		{
			if (*map_started == 1)
				*inside = 1;
		}
		else
		{
			if (*inside == 1)
				map_lines_exit("Error: Invalid line inside the map\n", line,
					map);
			*map_started = 1;
		}
	}
	free(line);
}

int	map_lines(int fd, t_map *map)
{
	char	*line;
	int		map_started;
	int		inside;

	map_started = 0;
	inside = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		process_line(line, map, &map_started, &inside);
	}
	return (0);
}
