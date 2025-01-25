/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trime.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 03:32:02 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:26:34 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

char	*trime_line(char *line)
{
	if (*line == '\0')
		return (NULL);
	while (*line)
	{
		if (*line == ' ' || *line == '\t' || *line == '\v')
			line++;
	}
	return (line);
}
