/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tex_util.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 04:51:47 by amezioun          #+#    #+#             */
/*   Updated: 2025/01/25 12:23:02 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

uint32_t	get_rgb_color(int *rgb)
{
	return (get_rgb(rgb[0], rgb[1], rgb[2], 255));
}

int	get_tex_x_pixel(float tex_x, mlx_texture_t *tex)
{
	int	tex_x_pixel;

	tex_x_pixel = (int)tex_x;
	if (tex_x_pixel < 0)
		tex_x_pixel = 0;
	else if ((uint32_t)tex_x_pixel >= tex->width)
		tex_x_pixel = tex->width - 1;
	return (tex_x_pixel);
}

void	adjust_draw_bounds(t_tex_params *p, int *draw_start, int *draw_end)
{
	*draw_start = p->wall_top;
	*draw_end = p->wall_top + p->wall_height;
	if (*draw_start < 0)
		*draw_start = 0;
	if (*draw_end >= WIN_HEIGHT)
		*draw_end = WIN_HEIGHT - 1;
}
