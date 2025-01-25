/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 02:11:19 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:24:56 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	store_textures(char index, char *line, t_map **map)
{
	if (index == 'E')
	{
		if ((*map)->ea)
			ft_exit("Error: EA texture already exist\n", *map);
		(*map)->ea = ft_strdup(line);
	}
	else if (index == 'N')
	{
		if ((*map)->no)
			ft_exit("Error: NO texture already exist\n", *map);
		(*map)->no = ft_strdup(line);
	}
	else if (index == 'W')
	{
		if ((*map)->we)
			ft_exit("Error: WE texture already exist\n", *map);
		(*map)->we = ft_strdup(line);
	}
	else if (index == 'S')
	{
		if ((*map)->so)
			ft_exit("Error: SO texture already exist\n", *map);
		(*map)->so = ft_strdup(line);
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
