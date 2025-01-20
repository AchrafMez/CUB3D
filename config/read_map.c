#include "../cub3.h"

void read_map(char *file_name, t_map **map)
{
    char *line = NULL;
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
            parse_colors(line, map);
        free(line);  
        line = get_next_line(fd);
    }
    close(fd);
    fill_map(fd, file_name, map);
}

