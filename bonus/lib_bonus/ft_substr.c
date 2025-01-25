/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 03:30:22 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:26:05 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	size;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	size = ft_strlen(s);
	if (*s == 0 || start > (unsigned int)(size - 1))
		return (ft_strdup(""));
	if (len <= (size - start))
		new = malloc(len + 1);
	else
		new = malloc((size - start) + 1);
	if (!new)
		return (NULL);
	while (s[i + start] && (i < len))
	{
		new[i] = s[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}
