#include "../cub3.h"

int fill_mapline_checker(char *end, char *line, int map_started)
{
    if (*end == '\0' && map_started == 0)
    {
        free(line);
        free(end);
        return 0;
    }
    else if(*end == '\0' && map_started == 1)
    {
        free(line);
        free(end);
        return 0;
    }
    return 1;
}

void fill_mapline(int map_line, int fd, t_map **map)
{
    if(map_line < 0)
        return ;
    (*map)->map = malloc(sizeof(char *) * (map_line + 1));
    if(!(*map)->map)
        return ;
    char *line = NULL;
    int map_started = 0;
    int i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        char *end = substring2(line);
        if(fill_mapline_checker(end, line, map_started) == 0)
            continue;
        if (is_map(end) == 0)
        {
            map_started = 1;
            (*map)->map[i] = ft_strdup(end);
            i++; 
        }
        free(end);
        free(line);
    }
    (*map)->map[i] = NULL;
}

void fill_map(int fd, char *file_namp, t_map **map)
{
    fd = open(file_namp, O_RDONLY);
    if(fd < 0)
    {
        perror("Error");
        return ;
    }
    close(fd);
    fd = open(file_namp, O_RDONLY);
    if(fd  < 0)
    {
        perror("Errror");
        return ;
    }
    close(fd);
    fd = open(file_namp, O_RDONLY);
    if(map_lines(fd, *map) == 0)
    {
        close(fd);
        fd = open(file_namp, O_RDONLY);
        int map_line = lines_count(fd, *map);
        if(map_line <= 0)
        {
            close(fd);
            ft_exit("Error: There is no map!\n", *map);
        }
        close(fd);
        fd = open(file_namp, O_RDONLY);
        fill_mapline(map_line, fd, map);
        close(fd);
    } else
    {
        close(fd);
        exit(EXIT_FAILURE);
    }
}
