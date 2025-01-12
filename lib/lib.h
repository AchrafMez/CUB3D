#ifndef LIB_H
#define LIB_H

#include "../cub3.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len);
int	ft_strlen(const char *s);
int	ft_atoi(const char *str);
char	**ft_split(char const *s, char c);
void	ft_putstr(char *s, int fd);
char *substring(char *line);
char *substring2(char *line);
char *trime_line(char *line);
char *skip_whiespaces(char *line);

#endif