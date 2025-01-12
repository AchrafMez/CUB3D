#include "../cub3.h"

void read_map(char *file_name, t_map **map)
{
    (void)map;  
    char *line = NULL;
    // printf("%s\n", file_name);
    int fd = open(file_name, O_RDONLY);
    if(fd < 0)
    {
        printf("fd failed\n");
        return ;
    }
    line = get_next_line(fd);
    while(line)
    {
        if(check_identif(line) == 0)
        {
            check_positions(line, 'N', 'O', map);
            check_positions(line, 'S', 'O', map);
            check_positions(line, 'W', 'E', map);
            check_positions(line, 'E', 'A', map);
        }
        if(check_FC(line, *map) == 0)
        {
            // count++;
            // printf("check fc true\n");
//            printf("color line: %s\n", line);
            parse_colors(line, map);
        }
        // if(is_map(line) == 0)
        // {
            // printf("here is the map lines\n");
            // printf("line: %s\n", line);
        // }
        free(line);  
        line = get_next_line(fd);
    }
    close(fd);
    fill_map(fd, file_name, map);
}