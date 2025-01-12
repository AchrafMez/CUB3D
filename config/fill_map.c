#include "../cub3.h"

void fill_mapline(int map_line, int fd, t_map **map)
{
    if(map_line < 0)
    {
        printf("there is no map\n");
        return ;
    }
    (*map)->map = malloc(sizeof(char *) * (map_line + 1));
//    printf("map line + 1 == %d\n", map_line + 1);
    if(!(*map)->map)
    {
        printf("allocation failed\n");
        return ;
    }
    char *line = NULL;
    int map_started = 0;
    int i = 0;
    while ((line = get_next_line(fd)) != NULL)
    {
        char *end = substring2(line);
//        printf("end: %s\n", end);
        if (*end == '\0' && map_started == 0)
        {
            // printf("here\n");
            free(line);
            free(end);
            continue;
        }
        else if(*end == '\0' && map_started == 1)
        {
            free(line);
            free(end);
            continue;
        }
        if (is_map(end) == 0)
        {
            // printf("heere\n");
//            printf("end in is map true: %s\n", end);
            map_started = 1;
            (*map)->map[i] = ft_strdup(end);
            // printf("map[%d]: %s\n", i,(*map)->map[i]);
            i++; 
        }
        // else if(is_map(end) == 1 && map_started == 1)
        // {
        //     printf("end: %s\n", end);
        //     printf("there is a problem inside the map\n");
        //     exit(1);
        // }
//        free(trimmed_line);
//        free(dup2);
        free(end);
        free(line);
    }
    // printf("i:   %d\n", i);
    (*map)->map[i] = NULL;
}

void fill_map(int fd, char *file_namp, t_map **map)
{
    // char *line;
//    (void)map;
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
    // printf("map lines: %d\n", map_line);
}