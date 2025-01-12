#include "../cub3.h"

char *substring(char *line)
{
    if(!line || *line == '\0')
        return NULL;
    int i = 0;
    while(line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
        i++;
    int start = i;
    int end = strlen(line) - 1;
    while(line[end] && (line[end] == ' ' || line[end] == '\t' || line[end] == '\v'))
        end--;
    char *substring = malloc((end - start) + 2);
    if(!substring)
        return NULL;
    i = 0;
    while(line[start] && start <= end)
    {
        substring[i] = line[start];
        i++;
        start++;
    }
    substring[i] = '\0';
    return substring;
}