#include "cub3.h"
#include <string.h>

int check_extension(char *file_name){
    
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

char *ft_substr(char *line)
{
    if(!line)
        return NULL;
    // int len = strlen(line);
    int i = 0;
    // if(line[len] == '\0')
        // len--;
    // while(line[len]  == ' ' || line[len] == '\t'){
        // len--;
    // }
    while(line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
        i++;
    int start = i;
    int end = strlen(line) - 1;
    // printf("end: %d\n", end);
    // if(line[end] == '\0')
        // end--;
    while(line[end] && (line[end] == ' ' || line[end] == '\t' || line[end] == '\v'))
        end--;
    // printf("start: %d\n", start);
    // printf("end: %d\n", end);
    // while(line[i] && line[i] != ' ')
    //     i++;
    // printf("len: %d\n", i - start + 1);
    char *substring = malloc((end - start) + 2);
    if(!substring)
        return NULL;
    i = 0;
    while(line[start] && start <= end)
    {
        // printf("%c\n", line[start]);
        substring[i] = line[start];
        i++;
        start++;
    }
    substring[i] = '\0';
    // printf("substring%s\n", substring);
    return substring;
}

int check_texture_perm(char *path)
{
    int fd = open(path, O_RDONLY);
    if(fd < 0)
    {
        perror("Error");
        return 1;
    }
    close(fd);
    return 0;
}

void store_textures(char index, char *line, t_map **map)
{
    if(index == 'E')
    {
        if((*map)->EA)
        {
            printf("Error: EA texture already exist\n");
            //here i should freeing and exit
            return ;
        }
        (*map)->EA = ft_strdup(line);
    }
    else if(index == 'N')
    {
        if((*map)->NO)
        {
            printf("Error: NO texture already exist\n");
            return ;
        }
        (*map)->NO = ft_strdup(line);
        // printf("map NO: %s\n", (*map)->NO);
        
    }
    else if(index == 'W')
    {
        if((*map)->WE)
        {
            printf("Error: WE texture already exist\n");
            return ;
        }
        (*map)->WE = ft_strdup(line);
    }
    else if(index == 'S')
    {
        if((*map)->SO)
        {
            printf("Error: SO texture already exist\n");
            return ;
        }
       (*map)->SO = ft_strdup(line);
    }
    else{
        printf("no position given\n");
    }
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
            char *path = ft_substr(line + i);
            printf("PATH: '%s'\n", path);
            // printf("'%c%c': '%s'\n", f, s, path);
            if(check_texture_perm(path) == 0)
            {
                // printf("texture exist\n");
                store_textures(f, path, map);
            }
            else
            {
                // printf("PATH: '%s'\n", path);
                printf("texture doesn't exist\n");
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
        {
            // printf("there is an id--------------------->%c%c\n", line[i] , line[i + 1]);
            return 0;
        }
        else if(line[i] == 'F' || line[i] == 'C')
        {
            // printf("there is an id--------------------->%c\n", line[i]);
            return 0;
        }
        i++;
    }
    return 1;
}

// int check(char *line, t_map **map)
// {
//     int i = 0;
//     while(line[i])
//     {
//         if(line[i] == 'N' && line[i + 1] == 'O')
//             check_positions(line, 'N', 'O', map);
//         else if(line[i] == 'S' && line[i + 1] == 'O')
//             check_positions(line, 'S', 'O', map);
//         else if(line[i] == 'W' && line[i + 1] == 'E')
//             check_positions(line, 'W', 'E', map);
//         else if(line[i] == 'E' && line[i + 1] == 'A')
//             check_positions(line, 'E', 'A', map);
//         else if(line[i] == 'F')
//         {
//             printf("fff here]n\n");
//             check_positions(line, 'F', ' ', map);
//         }
//         else if(line[i] == 'C')
//         {
//             printf("c here]n\n");
//             check_positions(line, 'C', ' ', map);
//         }
//         else{
//             printf("no edentifiers\n");
//             return 1;
//         }
//         i++;
//     }
//     return 0;
// }

int valid_color(char *line)
{
    int i = 0;
    while(line[i])
    {
        if(line[i] < '0' || line[i] > '9')
            return 1;
        i++;
    }
    return 0;
}

void parse_colors(char *line, t_map **map)
{
    int i = 0;
    (void)map;
    while(line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
        i++;
    if(line[i] == 'F' || line[i] == 'C')
        i++;
    char *floor = ft_substr(line + i);
    printf("fc: %s\n", floor);
    free(floor);
}
//i need to parse colors and store them in the map
//then go to parse the map lines

int check_fc_prototype(char *line)
{
    int i = 0;
    while(line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
        i++;
    int comma = 0;
    while(line[i])
    {
        if(line[i] == ',')
            comma++;
        if(line[i] >= '0' && line[i] <= '9' && line[i] != ',')
            
        i++;
    }
}

int check_FC(char *line)
{
    int i = 0;
    while(line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
        i++;
    if(line[i] == 'F' || line[i] == 'C')
    {
        i++;
        if(check_fc_prototype(line + i) == 0)
        return 0;
    }
    else 
        return 1;
}
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
        // printf("line:  %s\n", line);
        if(check_identif(line) == 0)
        {
            check_positions(line, 'N', 'O', map);
            check_positions(line, 'S', 'O', map);
            check_positions(line, 'W', 'E', map);
            check_positions(line, 'E', 'A', map);
            // parse_floor(line, map);
            // check_positions(line, 'F', ' ', map);
            // check_positions(line, 'C', ' ', map);
        }
        if(check_FC(line) == 0)
        {
            printf("check fc true\n");
            parse_colors(line, map);
        }

        free(line);  
        line = get_next_line(fd);
    }

}

void free_map(t_map *map)
{
    free(map->NO);
    free(map->EA);
    free(map->SO);
    free(map->WE);
    free(map->map);
    free(map);
}

void null_init(t_map *map)
{
    map->NO = NULL;
    map->SO = NULL;
    map->WE = NULL;
    map->EA = NULL;
    map->map = NULL;
    map->player_x = 0;
    map->player_y = 0;
}
void print_map(t_map *map)
{
    printf("NO: %s\n", map->NO);
    printf("SO: %s\n", map->SO);
    printf("WE: %s\n", map->WE);
    printf("EA: %s\n", map->EA);
    printf("player_x: %d\n", map->player_x);
    printf("player_y: %d\n", map->player_y);
}

int main(int ac, char **av){

    if(ac == 2)
    {
        t_map *map = malloc(sizeof(t_map));
        if(!map)
            return 1;
        null_init(map);
        // check_positions(av[1], 'N', 'O', &map);
        if(check_extension(av[1]))
        {
            // printf("correct");
            read_map(av[1], &map);
        }
        else
            printf("uncorrect");
        // print_map(map);
       free_map(map);
    }
    return 0;
}