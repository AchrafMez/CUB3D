/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:11:19 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 02:11:20 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"

void	store_textures(char index, char *line, t_map **map)
{
	if (index == 'E')
	{
		if ((*map)->EA)
			ft_exit("Error: EA texture already exist\n", *map);
		(*map)->EA = ft_strdup(line);
	}
	else if (index == 'N')
	{
		if ((*map)->NO)
			ft_exit("Error: NO texture already exist\n", *map);
		(*map)->NO = ft_strdup(line);
	}
	else if (index == 'W')
	{
		if ((*map)->WE)
			ft_exit("Error: WE texture already exist\n", *map);
		(*map)->WE = ft_strdup(line);
	}
	else if (index == 'S')
	{
		if ((*map)->SO)
			ft_exit("Error: SO texture already exist\n", *map);
		(*map)->SO = ft_strdup(line);
	}
}

int	check_texture_perm(char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("Error");
		return (1);
	}
	close(fd);
	return (0);
}
