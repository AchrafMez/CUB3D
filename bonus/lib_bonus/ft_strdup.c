/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 03:29:56 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:26:19 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

char	*ft_strdup(char *s1)
{
	int		i;
	int		strlen;
	char	*str;

	if (!s1)
		return (NULL);
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
