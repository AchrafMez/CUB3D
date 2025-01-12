#include "../cub3.h"

int check_map_walls(char **map)
{
    int i = 0;
//    int j = 0;
    while(map[i])
    {
        if(wall(map[i]) == 1)
        {
//            printf("'%c'\n);
        }
        else
            // printf("Invalid map\n");
        i++;
    }
    return 0;   
}

void check_filled_map(t_map *map)
{
    if(!map->map || map->ciel_rgb[0] == -1 || map->floor_rgb[0] == -1 || !map->EA || !map->NO || !map->SO || !map->WE)
        ft_exit("Error: Map not filled correctly!\n", map);
}


void check_ones(char *line)
{
    while(*line)
    {
        if(*line != '1' && *line != ' ')
        {
            printf("Error: first or second line '%c', %s\n", *line, line);
            exit(1);
        }
        line++;
    }
}

int check_map_chars(char **map)
{
    int i = 0;
    int j = 0;
    int player_count = 0;
    int index = 0;
     int end = 0;
//     printf("first line %s\n", map[0]);
     check_ones(map[0]);
    while (map[i]) {
//        printf("%s\n", map[i]);
        end = strlen(map[i])- 1;
        if(map[i][end] != '1' && map[i][end] != ' ')
        {
            printf("Error: Last character in the map\n");
            exit(1);
        }
        while(map[i][j] == ' ' || map[i][j] == '\t')
        {
//                printf("char: %d: '%c'", map[i][j], j);
                j++;
        }
        index = j;
        if(map[i][index] != '1'){
            printf("\nError: first character in the map '%c'\n", map[i][index]);
            exit(1);
        }
        while (map[i][j]) {
//            printf("char in while %c", map[i][j]);
            if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E') {
                printf("Error: %c", map[i][j]);
                exit(1);
                // ft_exit("Unexpected character in the map!\n", data);
            }
            if(map[i][j] == 'S' ||  map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W')
                player_count++;
            j++;
        }
        j = 0;
        i++;
    }
    if(player_count != 1)
    {
        printf("the map need one player\n");
        exit(1);
    }
//         printf("last line %s\n", map[i - 1]);
    check_ones(map[i - 1]);
    return 0;
}

void check_zeros(t_map *map, int i, int j)
{
    if(map->map[i][j + 1] == ' ' ||  map->map[i][j - 1] == ' ')
        ft_exit("Error: an area must be closed\n", map);
    if(ft_strlen(map->map[i - 1]) <= j || ft_strlen(map->map[i + 1]) <= j || map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ' )
            ft_exit("Error: an area must be closed\n", map);
}

void check_map_spaces(t_map *map)
{
    int i = 1;
    int j = 0;
    while(map->map[i])
    {
        while(map->map[i][j])
        {
            if(map->map[i][j] == '0' || map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'E' || map->map[i][j] == 'W')
            {
                check_zeros(map, i, j);
            }
            j++;
        }
        j = 0;
        i++;
    }
}