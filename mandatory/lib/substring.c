/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   substring.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 03:30:57 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 05:42:56 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

char	*substring(char *line)
{
	int		i;
	int		start;
	int		end;
	char	*substring;

	if (!line || *line == '\0')
		return (NULL);
	i = 0;
	while (line[i] && (line[i] == ' ' || line[i] == '\t' || line[i] == '\v'))
		i++;
	start = i;
	end = ft_strlen(line) - 1;
	while (line[end] && (line[end] == ' ' || line[end] == '\t'
			|| line[end] == '\v'))
		end--;
	substring = malloc((end - start) + 2);
	if (!substring)
		return (NULL);
	i = 0;
	while (line[start] && start <= end)
		substring[i++] = line[start++];
	substring[i] = '\0';
	return (substring);
}
