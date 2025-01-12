#include "../cub3.h"

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