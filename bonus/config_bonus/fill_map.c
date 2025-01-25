/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:09:03 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:25:40 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

int	fill_mapline_checker(char *end, char *line, int map_started)
{
	if (*end == '\0' && (map_started == 0))
	{
		free(line);
		free(end);
		return (0);
	}
	else if (*end == '\0' && map_started == 1)
	{
		free(line);
		free(end);
		return (0);
	}
	return (1);
}

void	init_map(t_map **map, int map_line)
{
	(*map)->map = malloc(sizeof(char *) * (map_line + 1));
	if (!(*map)->map)
		return ;
}

void	free_line_end(char *line, char *end)
{
	free(line);
	free(end);
}

void	fill_mapline(int map_line, int fd, t_map **map)
{
	char	*line;
	int		map_started;
	int		i;
	char	*end;

	line = NULL;
	map_started = 0;
	init_map(map, map_line);
	i = 0;
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		end = substring2(line);
		if (fill_mapline_checker(end, line, map_started) == 0)
			continue ;
		if (is_map(end) == 0)
		{
			map_started = 1;
			(*map)->map[i++] = ft_strdup(end);
		}
		free_line_end(line, end);
	}
	(*map)->map[i] = NULL;
}

void	fill_map(int fd, char *file_namp, t_map **map)
{
	int	map_line;

	fd = open(file_namp, O_RDONLY);
	if (fd < 0)
	{
		perror("Errror");
		return ;
	}
	if (map_lines(fd, *map) == 0)
	{
		close(fd);
		fd = open(file_namp, O_RDONLY);
		map_line = lines_count(fd, *map);
		if (map_line <= 0)
		{
			close(fd);
			ft_exit("Error: There is no map!\n", *map);
		}
		close(fd);
		fd = open(file_namp, O_RDONLY);
		fill_mapline(map_line, fd, map);
	}
	close(fd);
}
