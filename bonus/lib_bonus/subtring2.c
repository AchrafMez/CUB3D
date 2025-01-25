/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subtring2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 03:31:38 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:26:32 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

char	*substring2(char *line)
{
	int		end;
	char	*dup;

	if (!line || *line == '\0')
		return (ft_strdup(""));
	end = ft_strlen(line);
	if (line[end] == '\0')
		end--;
	while (end >= 0 && line[end] && (line[end] == ' ' || line[end] == '\t'))
		end--;
	dup = ft_substr(line, 0, end + 1);
	return (dup);
}
