#include "../cub3.h"

void free_fc(char **fc)
{
    int i = 0;
    while(fc[i])
    {
        free(fc[i]);
        i++;
    }
    free(fc);
}

void fre_maplines(char **map)
{
    int i = 0;
    if(!map)
        return ;
    while(map[i] != NULL)
    {
        free(map[i]);
        i++;
    }
    free(map);
}
void free_map(t_map *map)
{
    free((void *)map->NO);
    free((void *)map->EA);
    free((void *)map->SO);
    free((void *)map->WE);
    free(map->floor_rgb);
    free(map->ciel_rgb);
    fre_maplines(map->map);
    free(map);
}

void ft_exit(char *str ,t_map *map)
{
    ft_putstr(str ,2);
    free_map(map);
    exit(EXIT_FAILURE);
}