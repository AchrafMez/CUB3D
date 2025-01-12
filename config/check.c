#include "../cub3.h"

int check_extension(char *file_name)
{
    
    const char extension[5]= ".cub";
    int check_counter = 3;
    int file_counter = strlen(file_name) - 1;
    while(check_counter >= 0 && extension[check_counter])
    {
        if(file_name[file_counter--] != extension[check_counter--])
            return 0;
    }
    return 1;
}

int check_color(char *fc, t_map *map)
{

//    int digit = 0;
        while((*fc ==' ' || *fc =='\t'))
        {
            // printf("char in spaces: '%c'\n",*fc);
            fc++;
        }
        if(*fc == '\0')
            ft_exit("Error: empty RGB part\n", map);
        while(isdigit(*fc) != 0)
        {
            // printf("char in digit: '%c'\n",*fc);
            fc++;
        }
        while((*fc ==' ' || *fc =='\t'))
        {
            // printf("char in spaces: '%c'\n",*fc);
            fc++;
        }
        if(*fc != '\0')
            ft_exit("Error: Invalid Color format\n", map);
        return 0;
}

int check_positions(char *line, char f, char s, t_map **map)
{
    (void)map;

    int i = 0;
    while(line[i])
    {
        if(line[i] == f && line[i+1] == s)
        {
            i+= 2;
            while(line[i] == ' ' || line[i] == '\t' || line[i] == '\v')
                i++;
            char *path = substring(line + i);
            if(check_texture_perm(path) == 0)
                store_textures(f, path, map);
            else
            {
                free(line);
                free(path);
                printf("some error here\n");
                exit(EXIT_FAILURE);
            }
            free(path);
            return 0;
        }
        i++;
    }
    return 1;
}

int check_identif(char *line)
{
    int i = 0;
    while(line[i])
    {
        if((line[i] == 'N' && line[i + 1] == 'O') || (line[i] == 'S' && line[i + 1] == 'O') || (line[i] == 'W' && line[i + 1] == 'E') || (line[i] == 'E' && line[i + 1] == 'A'))
            return 0;
        else if(line[i] == 'F' || line[i] == 'C')
            return 0;
        i++;
    }
    return 1;
}

int check(char *line, t_map **map)
{
    int i = 0;
    while(line[i])
    {
        if(line[i] == 'N' && line[i + 1] == 'O')
            check_positions(line, 'N', 'O', map);
        else if(line[i] == 'S' && line[i + 1] == 'O')
            check_positions(line, 'S', 'O', map);
        else if(line[i] == 'W' && line[i + 1] == 'E')
            check_positions(line, 'W', 'E', map);
        else if(line[i] == 'E' && line[i + 1] == 'A')
            check_positions(line, 'E', 'A', map);
        else if((line[i] == 'F' && line[i+1] == ' ') || (line[i] == 'C' && line[i + 1] == ' '))
        {
            if(check_FC(line, *map) == 0)
                parse_colors(line, map);
        }
        else{
            printf("%s:  no edentifiers\n", line);
            // exit(1);
            return 1;
        }
        i++;
    }
    return 0;
}