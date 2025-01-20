#include "../cub3.h"

void store_FC(char **fc, int flag, t_map **map)
{
    int i = 0;

    if(flag == 0)
        {
            while(fc[i])
            {
                if((*map)->floor_rgb[i] == -1)
                    (*map)->floor_rgb[i] = ft_atoi(fc[i]);
                else if((*map)->floor_rgb[i] != -1)
                    ft_exit("Error : Floor color already exist\n", *map);
                i++;
            }
            i = 0;
        }
        else if(flag == 1){
            i = 0;
            while(fc[i])
            {
                if((*map)->ciel_rgb[i] == -1){
                    (*map)->ciel_rgb[i] = ft_atoi(fc[i]);
                }
                else if((*map)->ciel_rgb[i] != -1)
                    ft_exit("Error : Ciel color already exist\n", *map);
                i++;
            }
            i = 0;
        }
}

int check_fc_prototype(char *line, t_map *map)
{
    unsigned long i = 0;
    while(line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
        i++;
    int comma = 0;
    while(line[i])
    {
        if(line[i] == ',')
            comma++;
        if(isdigit(line[i]) == 0 && line[i] != ',' && line[i] != ' ')
            return 1;
        i++;
    }
    if(comma != 2)
        ft_exit("Error: Invalid color format\n", map);
    if(i == (strlen(line)))
        return 0;
    return 1;
}

int check_FC(char *line, t_map *map)
{
    int i = 0;
    while(line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
        i++;
    if(((line[i] == 'F' && line[i+1] != '\t') && (line[i] == 'F' && line[i+1] != ' ')) || ((line[i] == 'C' && line[i+1] != '\t') && (line[i] == 'C' && line[i+1] != ' ')))
        ft_exit("Error: F or C Not filled as expected\n", map);
    if((line[i] == 'F' && line[i+1] == ' ') || (line[i] == 'F' && line[i+1] == '\t') ||  (line[i] == 'C' && line[i + 1] == ' ') || (line[i] == 'C' && line[i+1] == '\t'))
    {
        i++;
        if(check_fc_prototype(line + i, map) == 0)
            return 0;
    }
    return 1;
}

void fill_colors(char *line, t_map **map, int flag)
{
    char **fc = ft_split(line, ',');
    if(valide_color(fc, *map) == 0)
        store_FC(fc, flag, map);
    else
    {
        free_fc(fc);
        ft_exit("Error : Color not valid\n", *map);
    }
    free_fc(fc);
}
