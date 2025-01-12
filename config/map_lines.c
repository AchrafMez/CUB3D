#include "../cub3.h"

int lines_count(int fd, t_map *map)
{
    char *line;
    int map_started = 0;
    int count = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        char *trimmed_line = skip_whiespaces(line);
        if (*trimmed_line == '\0' && map_started == 0)
        {
            free(line);
            continue;
        }
        else if (*trimmed_line == '\0' && map_started == 1)
        {
//            printf("empty lines inside map\n");
            free(line);
            continue ;
//            exit(EXIT_FAILURE);
        }

        else if (is_map(trimmed_line) == 0)
        {
            // printf("line in map lines: %s\n", trimmed_line);
            map_started = 1;
            //store map
            count++;
        }
        else if (map_started == 1)
        {
            free(line);
            ft_exit("Error: Invalid line inside the map\n", map);
        }

        free(line);
    }
    return count;
}





int map_lines(int fd, t_map *map)
{
    char *line;
    int map_started = 0;
    int inside = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        char *trimmed_line = skip_whiespaces(line);
//        printf("trimmed: '%s'\n", trimmed_line);
        if (valid_map(trimmed_line) == 0) {
            free(line);
            ft_exit("Error: Invalid character inside the map\n", map);
        }
        if(is_map(trimmed_line) == 0)
        {
            if (*trimmed_line == '\0')
            {
                if(map_started == 1)
                        inside = 1;
            }
            else{
                if(inside == 1)
                {
                    free(line);
                    ft_exit("Error: Invalid line inside the map\n", map);
                }
                map_started = 1;
            }
        }
        free(line);
    }
    return 0;
}