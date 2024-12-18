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
    while(line[i] && line[i] != ' ')
        i++;
    printf("len: %d\n", i - start + 1);
    char *substring = malloc((i - start) + 1);
    if(!substring)
        return NULL;
    i = 0;
    while(line[start] && line[start] != ' ')
    {
        printf("%c\n", line[start]);
        substring[i] = line[start];
        i++;
        start++;
    }
    substring[i] = '\0';
    printf("substring%s\n", substring);
    return substring;
}

int check_texture_perm(char *path)
{
    int fd = open(path, O_RDONLY);
    if(fd < 0)
    {
        perror("error");
        return 1;
    }
    close(fd);
    return 0;
}

void store_textures(char index, char *line, t_map **map)
{
    if(index == 'E')
    {
        printf("E\n");
        (*map)->EA = ft_strdup(line);

        // if((*map)->EA)
            // printf("map ea: %s\n", (*map)->EA);
    }
    else if(index == 'N')
    {
        (*map)->NO = ft_strdup(line);
        printf("map NO: %s\n", (*map)->NO);
        
    }
    else if(index == 'W')
        (*map)->WE = ft_strdup(line);
    else if(index == 'S')
       (*map)->SO = ft_strdup(line);
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
            // while(line[i] == ' ' || line[i] == '\t' || line[i] == '\v')
            //     i++;
            // char *path = ft_substr(line + i);
            // printf("'%c%c': '%s'\n", f, s, path);
            if(check_texture_perm("") == 0)
            {
                printf("texture exist\n");
                // store_textures(f, path, map);
            }
            else{
                printf("texture problem\n");
            }
            // free(path);
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
            printf("there is an id--------------------->%c%c\n", line[i] , line[i + 1]);
            return 0;
        }
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
        else{
            printf("no edentifiers\n");
            return 1;
        }
        // else if(line[i] == 'F')
        //     check_positions(line, 'N', '*', map);
        // else if(line[i] == 'C')
        //     check_positions(line, 'N', '*', map);
        i++;
    }
    return 0;
}
void read_map(char *file_name, t_map **map)
{
    (void)map;
    char *line = NULL;
    printf("%s\n", file_name);
    int fd = open(file_name, O_RDONLY);
    if(fd < 0)
    {
        printf("fd failed\n");
        return ;
    }
    line = get_next_line(fd);
    while(line)
    {
        // printf("%s\n", line);
        // if(check_identif(line) == 0)
        // {
            check_positions(line, 'N', 'O', map);
        // }
        free(line);  
        line = get_next_line(fd);
    }

}

void free_map(t_map *map)
{
    free(map->NO);
    free(map);
}

int main(int ac, char **av){

    if(ac == 2)
    {
        t_map *map = malloc(sizeof(t_map));
        if(!map)
            return 1;
        // check_positions(av[1], 'N', 'O', &map);
        if(check_extension(av[1]))
        {
            printf("correct");
            read_map(av[1], &map);
        }
        else
            printf("uncorrect");
       free_map(map);
    }
    return 0;
}