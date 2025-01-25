/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 03:08:54 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 03:08:57 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	texture_position(char *line, t_map **map)
{
	check_positions(line, 'N', 'O', map);
	check_positions(line, 'S', 'O', map);
	check_positions(line, 'W', 'E', map);
	check_positions(line, 'E', 'A', map);
}

void	read_map(char *file_name, t_map **map)
{
	char	*line;
	int		fd;

	line = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
	{
		printf("fd failed\n");
		return ;
	}
	line = get_next_line(fd);
	while (line)
	{
		if (check_identif(line) == 0)
			texture_position(line, map);
		if (check_fc(line, *map) == 0)
			parse_colors(line, map);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	fill_map(fd, file_name, map);
}
