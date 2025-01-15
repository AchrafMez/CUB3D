#include "../cub3.h"


void parse_colors(char *line, t_map **map)
{
    // int i = 0;
    (void)map;
    while(*line && (*line == ' ' || *line == '\t' || *line == '\v'))
        line++;
    if(*line == 'F')
    {
        line++;
        char *floor = substring(line);
            fill_colors(floor, map, 0);
        free(floor);
    }
    else if(*line == 'C')
    {
        line++;
        char *floor = substring(line);
        fill_colors(floor, map, 1);
        free(floor);
    }
}



int is_map(char *line)
{
    int i = 0;
    if(!line)
        return 0;
    while(line[i])
    {
        if(line[i] != ' ' && line[i] != '\t' && line[i] != '1' && line[i] != '0' && line[i] != 'W' && line[i] != 'E' && line[i] != 'S' && line[i] != 'N')
            return 1;
        i++;
    }
    return 0;
}

int empty_line(char *line)
{
    if(!line)
        return 1;
    while(*line)
    {
        if(*line != ' ' && *line != '\t')
            return 1;
        line++;
    }
    return 0;
}



int wall(char *map)
{
    int i = 0;
    while(map[i])
    {
        if(map[i] == ' ' || map[i] == '\t')
            i++;
        if(map[i] == '1')
        {
            printf("'%c'\n", map[i]);
            return 1;
        }
        else
            return 0;
        i++;
    }
    return 0;
}




void WHXY(t_map **map)
{
    int i = 0;
    int j = 0;
    int w = 0;
        w = ft_strlen((*map)->map[i]);
    while((*map)->map[i]){
		if(ft_strlen((*map)->map[i]) >= w)
			(*map)->WIDHT = ft_strlen((*map)->map[i]);
        if ((*map)->map[i + 1] && w < ft_strlen((*map)->map[i + 1]))
        {
        //    printf("w: %lu i+1 : %lu\n", w, ft_strlen((*map)->map[i+1]));
            w = ft_strlen((*map)->map[i + 1]);
        }
        while((*map)->map[i][j]){
            if((*map)->map[i][j] == 'S' || (*map)->map[i][j] == 'W' || (*map)->map[i][j] == 'E' || (*map)->map[i][j] == 'N')
            {
                (*map)->player = (*map)->map[i][j];
                (*map)->player_y = i;
                (*map)->player_x = j ;
            }
            j++;
        }
        j = 0;
        i++;
    }
    (*map)->HEIGHT = i;
}


int is_WESN(char c)
{
    if(c != 'N' && c != 'E' && c != 'S' && c != 'W')
        return 1;
    return 0;
}

