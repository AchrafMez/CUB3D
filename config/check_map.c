
#include "../cub3.h"

void	check_filled_map(t_map *map)
{
	if (!map->map || map->ciel_rgb[0] == -1 || map->floor_rgb[0] == -1
		|| !map->EA || !map->NO || !map->SO || !map->WE)
		ft_exit("Error: Map not filled correctly!\n", map);
}

void	check_ones(char *line, t_map *map)
{
	while (*line)
	{
		if (*line != '1' && *line != ' ')
			ft_exit("Error: Invalid character in the first or last line", map);
		line++;
	}
}

void	check_map_last_char(t_map *map, int i)
{
	int	end;

	end = 0;
	check_ones(map->map[0], map);
	end = strlen(map->map[i]) - 1;
	if (map->map[i][end] != '1' && map->map[i][end] != ' ')
		ft_exit("Error: Last character in the map\n", map);
}

void	check_map_char(t_map *map, int i, int *player_count)
{
	int	j;

	j = 0;
	while (map->map[i][j] == ' ' || map->map[i][j] == '\t')
		j++;
	if (map->map[i][j] != '1')
		ft_exit("Error: first character in the map\n", map);
	while (map->map[i][j])
	{
		if (map->map[i][j] != '1' && map->map[i][j] != '0'
			&& map->map[i][j] != ' ' && map->map[i][j] != 'N'
			&& map->map[i][j] != 'S' && map->map[i][j] != 'W'
			&& map->map[i][j] != 'E')
			ft_exit("Error: Unexpected character in the map!\n", map);
		if (map->map[i][j] == 'S' || map->map[i][j] == 'N'
			|| map->map[i][j] == 'E' || map->map[i][j] == 'W')
			(*player_count)++;
		j++;
	}
}

int	check_map_chars(t_map *map)
{
	int	i;
	int	player_count;

	i = 0;
	player_count = 0;
	while (map->map[i])
	{
		check_map_last_char(map, i);
		check_map_char(map, i, &player_count);
		i++;
	}
	if (player_count != 1)
		ft_exit("Error: The map needs one player\n", map);
	check_ones(map->map[i - 1], map);
	return (0);
}

void	check_zeros(t_map *map, int i, int j)
{
	if (map->map[i][j + 1] == ' ' || map->map[i][j - 1] == ' ')
		ft_exit("Error: an area inside the map must be closed\n", map);
	if (ft_strlen(map->map[i - 1]) <= j || ft_strlen(map->map[i + 1]) <= j
		|| map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ')
		ft_exit("Error: an area inside the map must be closed\n", map);
}

void	check_map_spaces(t_map *map)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (map->map[i])
	{
		while (map->map[i][j])
		{
			if (map->map[i][j] == '0' || map->map[i][j] == 'N'
				|| map->map[i][j] == 'S' || map->map[i][j] == 'E'
				|| map->map[i][j] == 'W')
				check_zeros(map, i, j);
			j++;
		}
		j = 0;
		i++;
	}
}
