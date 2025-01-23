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
int	lines_count(int fd, t_map *map)
{
	char	*line;
	int		map_started;
	int		count;
	char	*trimmed_line;

	map_started = 0;
	count = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed_line = skip_whiespaces(line);
		if (lines_count_checker(trimmed_line, map_started, line) == 0)
			continue ;
		else if (is_map(trimmed_line) == 0)
		{
			map_started = 1;
			count++;
		}
		else if (map_started == 1)
		{
			free(line);
			ft_exit("Error: Invalid line inside the map\n", map);
		}
		free(line);
	}
	return (count);
}


static void	check_map_line(int map_started, int inside, char *trimmed_line, t_map *map)
{
	if (*trimmed_line == '\0')
	{
		if (map_started == 1)
			inside = 1;
	}
	else
	{
		if (inside == 1)
			ft_exit("Error: Invalid line inside the map\n", map);
		map_started = 1;
	}
}
int	map_lines(int fd, t_map *map)
{
	char	*line;
	int		map_started;
	int		inside;
	char	*trimmed_line;

	map_started = 0;
	inside = 0;
	while ((line = get_next_line(fd)) != NULL)
	{
		trimmed_line = skip_whiespaces(line);
		if (valid_map(trimmed_line) == 0)
		{
			free(line);
			ft_exit("Error: Invalid character inside the map\n", map);
		}
		if (is_map(trimmed_line) == 0)
            check_map_line(map_started, inside, trimmed_line, map);
		free(line);
	}
	return (0);
}
