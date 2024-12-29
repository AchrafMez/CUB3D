#include "cub3.h"

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

char *substring(char *line)
{
    if(!line || *line == '\0')
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


void free_fc(char **fc)
{
    int i = 0;
    while(fc[i])
    {
        free(fc[i]);
        i++;
    }
    free(fc);
}

void fre_maplines(char **map)
{
    int i = 0;
    if(!map)
        return ;
    while(map[i] != NULL)
    {
        free(map[i]);
        i++;
    }
    free(map);
}
void free_map(t_map *map)
{
    free(map->NO);
    free(map->EA);
    free(map->SO);
    free(map->WE);
    free(map->floor_rgb);
    free(map->ciel_rgb);
    fre_maplines(map->map);
    free(map);
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


void	ft_putstr(char *s, int fd)
{
    int	i;

    i = 0;
    while (s[i] != '\0')
    {
        write(fd, &s[i], 1);
        i++;
    }
}

void ft_exit(char *str ,t_map *map)
{
    ft_putstr(str ,2);
    free_map(map);
    exit(EXIT_FAILURE);
}

void store_textures(char index, char *line, t_map **map)
{
    if(index == 'E')
    {
        if((*map)->EA)
            ft_exit("Error: EA texture already exist\n", *map);
        (*map)->EA = ft_strdup(line);
    }
    else if(index == 'N')
    {
        if((*map)->NO)
            ft_exit("Error: NO texture already exist\n", *map);
        (*map)->NO = ft_strdup(line);
    }
    else if(index == 'W')
    {
        if((*map)->WE)
            ft_exit("Error: WE texture already exist\n", *map);
        (*map)->WE = ft_strdup(line);
    }
    else if(index == 'S')
    {
        if((*map)->SO)
            ft_exit("Error: SO texture already exist\n", *map);
        (*map)->SO = ft_strdup(line);
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
            char *path = substring(line + i);
            if(check_texture_perm(path) == 0)
                store_textures(f, path, map);
            else
            {
                free(line);
                free(path);
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

void print_fc(char **fc)
{
    int i = 0;
    while(fc[i])
        printf("rgb: %s\n", fc[i++]);
}

void init_floor(t_map **map)
{
    (*map)->floor_rgb = malloc(sizeof(int) * 3);
    if(!(*map)->floor_rgb)
        return ;
    (*map)->floor_rgb[0] = -1;
    (*map)->floor_rgb[1] = -1;
    (*map)->floor_rgb[2] = -1;
}

void init_ciel(t_map **map)
{
    (*map)->ciel_rgb = malloc(sizeof(int) * 3);
    if(!(*map)->ciel_rgb)
        return ;
    (*map)->ciel_rgb[0] = -1;
    (*map)->ciel_rgb[1] = -1;
    (*map)->ciel_rgb[2] = -1;
}


int check_color(char *fc)
{

//    int digit = 0;
        while((*fc ==' ' || *fc =='\t'))
        {
            // printf("char in spaces: '%c'\n",*fc);
            fc++;
        }
        if(*fc == '\0')
        {
            // printf("emprty string color\n");
            return  0;
        }
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
        {
            // printf("uncorrect color format\n");
            exit(EXIT_FAILURE);
        }
        return 0;
}
int valide_color(char **fc, t_map *map)
{
    int i = 0;
    while(fc[i])
    {
        // printf("color: '%s'\n", fc[i]);
        if(check_color(fc[i]) == 0)
        {
            // printf("%d\n", ft_atoi(fc[i]));
            if(ft_atoi(fc[i]) < 0 || ft_atoi(fc[i]) > 255)
                return 1;
        } else
        {
            ft_exit("Error: Not a valid color\n", map);
        }

        i++;
    }
    if(i != 3)
    {
        // printf("i in valide coloe %d\n", i);
        ft_exit("Error: Not a valid color\n", map);
    }
    return 0;
}

void print_color(t_map *map)
{
    if(map->floor_rgb)
        printf("floor %d %d %d\n", map->floor_rgb[0], map->floor_rgb[1], map->floor_rgb[2]);
    if(map->ciel_rgb)
        printf("ciel %d %d %d\n", map->ciel_rgb[0], map->ciel_rgb[1], map->ciel_rgb[2]);
}
void store_FC(char **fc, int flag, t_map **map){
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
                {
                    // printf("ciel color %d\n", (*map)->ciel_rgb[i]);
                    ft_exit("Error : Ciel color already exist\n", *map);
                }
                i++;
            }
            i = 0;
        }
}

void fill_colors(char *line, t_map **map, int flag)
{
    char **fc = ft_split(line, ',');
    // printf("flag in fill color = %d\n", flag);
    if(valide_color(fc, *map) == 0)
    {
        // printf("hnaa\n");
        store_FC(fc, flag, map);
    }
    else
    {
        free_fc(fc);
        ft_exit("Error : Color not valid\n", *map);
    }
    free_fc(fc);
}

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

int check_fc_prototype(char *line, t_map *map)
{
    unsigned long i = 0;
    while(line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
        i++;
    int comma = 0;
    while(line[i])
    {
        // printf("FC:    '%c'\n", line[i]);
        if(line[i] == ',')
        {
            comma++;
            // printf("comma %d\n", comma);
        }
        if(isdigit(line[i]) == 0 && line[i] != ',' && line[i] != ' ')
        {
            // printf("line[i]: %c", line[i]);
            // printf("not a valid color\n");
            return 1;
        }
        i++;
    }
    if(comma != 2)
        ft_exit("Error: Invalid color format\n", map);
    if(i == (strlen(line)))
    {
        // printf("correct colors\n");
        return 0;
    }
    // printf("not correct colors");
    return 1;
}

int check_FC(char *line, t_map *map)
{
    int i = 0;
    while(line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
        i++;
    if(line[i] == 'F' || line[i] == 'C')
    {
        i++;
        if(check_fc_prototype(line + i, map) == 0)
        {
            // printf("colors is good\n");
            return 0;
        }
    }
    return 1;
}

int is_map(char *line)
{
    int i = 0;
    if(!line)
        return 0;
    while(line[i])
    {
        if(line[i] != ' ' && line[i] != '1' && line[i] != '0' && line[i] != 'W' && line[i] != 'E' && line[i] != 'S' && line[i] != 'N')
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

char *trime_line(char *line)
{
    if(*line == '\0')
        return NULL;
    while(*line)
    {
        if(*line == ' ' || *line == '\t' || *line == '\v')
            line++;
    }
    return line;
}


int is_start(char *line)
{
    if(*line == '\0')
        return 1;
    return 0;
}

char *skip_whiespaces(char *line)
{
    while(*line && (*line == ' ' || *line == '\t' || *line == '\v'))
        line++;
    return line;
}



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

int valid_map(char *line) {
    while (*line == ' ' || *line == '\t' || *line == '\v')
        line++;
    if (*line == '\0' || *line == ' ' || *line == '\t' || *line == '\v' ||
        *line == '1' ||
        (*line == 'S' && *(line+1) == 'O') ||
        (*line == 'W' && *(line + 1) == 'E') ||
        (*line == 'N' && *(line+ 1) == 'O') ||
        (*line == 'E' && *(line+1) == 'A') ||
        *line == 'F' || *line == 'C') {
        // printf("line: '%c'\n ", *line);
        return 0;
    }
    // printf("line: '%c' string: %s\n ", *line, line);
    return 1;
}

int map_lines(int fd, t_map *map)
{
    char *line;
    int map_started = 0;
    int inside = 0;

    while ((line = get_next_line(fd)) != NULL)
    {
        char *trimmed_line = skip_whiespaces(line);
        if (valid_map(trimmed_line) == 1) {
            printf("trimmed line: '%s'\n", trimmed_line);
            free(line);
            ft_exit("Error: Invalid map\n", map);
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

char *substring2(char *line)
{
    if(!line || *line == '\0')
    {
//        return NULL;
        return ft_strdup("");
    }
    int end = strlen(line);
    if(line[end] == '\0')
        end--;
    while(end >= 0 && line[end] && (line[end] == ' ' || line[end] == '\t'))
            end--;
//    printf("%d\n", end);
    char *dup = ft_substr(line, 0, end + 1);
    return dup;
}


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
        printf("end: %s\n", end);
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
        else if(line[i] == 'F' || line[i] == 'C')
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



void null_init(t_map *map)
{
    map->NO = NULL;
    map->SO = NULL;
    map->WE = NULL;
    map->EA = NULL;
    map->map = NULL;
    map->player_x = 0;
    map->player_y = 0;
    init_ciel(&map);
    init_floor(&map);
}


void print_maplines(char **map)
{
    int i = 0;
    while(map[i])
        printf("map lines: %s\n", map[i++]);
}
void print_map(t_map *map)
{
    printf("---------------map--------------\n");
    printf("NO: %s\n", map->NO);
    printf("SO: %s\n", map->SO);
    printf("WE: %s\n", map->WE);
    printf("EA: %s\n", map->EA);
    printf("player_x: %d\n", map->player_x);
    printf("player_y: %d\n", map->player_y);
    print_color(map);
    print_maplines(map->map);
    printf("---------------map--------------\n");

}

void leak()
{
    system("leaks cub3");
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

int check_map_walls(char **map)
{
    int i = 0;
//    int j = 0;
    while(map[i])
    {
        if(wall(map[i]) == 1)
        {
//            printf("'%c'\n);
        }
        else
            // printf("Invalid map\n");
        i++;
    }
    return 0;   
}

void check_filled_map(t_map *map)
{
    if(!map->map || map->ciel_rgb[0] == -1 || map->floor_rgb[0] == -1 || !map->EA || !map->NO || !map->SO || !map->WE)
        ft_exit("Error: Map not filled correctly!\n", map);
}

int check_map_chars(char **map){
    int i = 0;
    int j = 0;
    int player_count = 0;
    // int end = 0;
    while (map[i]) {
        printf("%s\n", map[i]);
        // end = strlen(map[i]);
        // if(map[i][end] != '1')
        // {
        //     printf("map should closed by ones '1, %c", map[i][end]);
        //     exit(1);
        // }
        while (map[i][j]) {
            if (map[i][j] != '1' && map[i][j] != '0' && map[i][j] != ' ' && map[i][j] != 'N' && map[i][j] != 'S' && map[i][j] != 'W' && map[i][j] != 'E') {
                printf("Error: %c", map[i][j]);
                exit(1);
                // ft_exit("Unexpected character in the map!\n", data);
            }
            if(map[i][j] == 'S' ||  map[i][j] == 'N' || map[i][j] == 'E' || map[i][j] == 'W')
                player_count++;
            j++;
        }
        j = 0;
        i++;
    }
    if(player_count != 1)
    {
        printf("the map need one player\n");
        exit(1);
    }
    return 0;
}

int main(int ac, char **av){

    if(ac == 2)
    {
        t_map *map = malloc(sizeof(t_map));
        if(!map)
            return 1;
        null_init(map);
        // check_positions(av[1], 'N', 'O', &map);
        // check_positions(av[1], 'N', 'O', &map);
        if(check_extension(av[1]))
        {
            // printf("correct");
            read_map(av[1], &map);
            check_filled_map(map);
            check_map_chars(map->map);
            // if(map->map) {
//               check_map_walls(map->map);
            //    }
            print_map(map);
            free_map(map);
        }
        else
            printf("Uncorrect filename\n");
    //    atexit(leak);
    }
    return 0;
}
