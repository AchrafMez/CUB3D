#include "../cub3.h"

char	*ft_strdup(char *s1)
{
	int		i;
	int		strlen;
	char	*str;

	i = 0;
	strlen = ft_strlen(s1);
	str = (char *)malloc(sizeof(char) * (strlen + 1));
	if (str == NULL)
		return (NULL);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}