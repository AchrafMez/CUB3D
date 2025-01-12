#include "../cub3.h"

char *skip_whiespaces(char *line)
{
    while(*line && (*line == ' ' || *line == '\t' || *line == '\v'))
        line++;
    return line;
}