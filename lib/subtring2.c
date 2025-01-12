#include "../cub3.h"

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