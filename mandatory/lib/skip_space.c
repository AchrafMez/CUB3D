/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_space.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 03:30:48 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 03:30:50 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

char	*skip_whiespaces(char *line)
{
	while (*line && (*line == ' ' || *line == '\t' || *line == '\v'))
		line++;
	return (line);
}
