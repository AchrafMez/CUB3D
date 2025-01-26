/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amezioun <amezioun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/22 10:29:59 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/26 10:26:59 by amezioun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3_bonus.h"

void	_set_player_pos(t_data *data, int32_t x, int32_t y)
{
	if (!is_collision(data, x, y))
	{
		data->player->pl->instances->x = x;
		data->player->pl->instances->y = y;
	}
}

void	update_player_pos(t_data *data)
{
	t_player	*player;
	int32_t		new_x;
	int32_t		new_y;
	double		move_step;

	player = data->player;
	player->rotation_angle += player->turn_direction * player->rotation_speed;
	move_step = player->walk_direction * player->move_speed;
	if (player->walk)
	{
		player->side_angle = player->rotation_angle + (M_PI / 2);
		new_x = player->pl->instances->x
			+ round(cos(player->side_angle) * move_step);
		new_y = player->pl->instances->y
			+ round(sin(player->side_angle) * move_step);
		player->walk = false;
	}
	else
	{
		new_x = player->pl->instances->x
			+ round(cos(player->rotation_angle) * move_step);
		new_y = player->pl->instances->y
			+ round(sin(player->rotation_angle) * move_step);
	}
	_set_player_pos(data, new_x, new_y);
}

void	render_all(t_data *data)
{
	t_ray	**rays;
	int		i;

	render_minimap(data);
	gun_animation(data);
	update_player_pos(data);
	mouse_handling(data);
	rays = cast_all_rays(data);
	render_walls(rays, data);
	i = -1;
	while (++i < WIN_WIDTH)
		free(rays[i]);
	free(rays);
}
void toggle_door(t_data *data, int x, int y)
{
    double dist = sqrt(pow(data->player->pl->instances->x - (x * TILE_SIZE), 2) + 
                       pow(data->player->pl->instances->y - (y * TILE_SIZE), 2));
    
    if (dist <= TILE_SIZE * 2)
    {
        if (data->map->map[y][x] == 'D')
            data->map->map[y][x] = 'O';
        else if (data->map->map[y][x] == 'O')
            data->map->map[y][x] = 'D';
    }
}

void handle_door_interaction(t_data *data)
{
    int player_map_x = (int)(data->player->pl->instances->x / TILE_SIZE);
    int player_map_y = (int)(data->player->pl->instances->y / TILE_SIZE);
    
    int check_offsets[][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};
    for (int i = 0; i < 4; i++)
    {
        int door_x = player_map_x + check_offsets[i][0];
        int door_y = player_map_y + check_offsets[i][1];
        
        if (data->map->map[door_y][door_x] == 'D' || 
            data->map->map[door_y][door_x] == 'O')
        {
            toggle_door(data, door_x, door_y);
            break;
        }
    }
}

   
void ft_keys(t_data *data)
{
 static bool e_key_pressed = false;

    if (mlx_is_key_down(data->map->mlx, MLX_KEY_W))
        data->player->walk_direction = 1;
    else if (mlx_is_key_down(data->map->mlx, MLX_KEY_S))
        data->player->walk_direction = -1;
    else if (mlx_is_key_down(data->map->mlx, MLX_KEY_A))
    {
        data->player->walk = true;
        data->player->walk_direction = -1;
    }
    else if (mlx_is_key_down(data->map->mlx, MLX_KEY_D))
    {
        data->player->walk = true;
        data->player->walk_direction = 1;
    }
    else
        data->player->walk_direction = 0;
    if (mlx_is_key_down(data->map->mlx, MLX_KEY_RIGHT))
        data->player->turn_direction = 1;
    else if (mlx_is_key_down(data->map->mlx, MLX_KEY_LEFT))
        data->player->turn_direction = -1;
    else
        data->player->turn_direction = 0;

   if (mlx_is_key_down(data->map->mlx, MLX_KEY_E))
    {
        if (!e_key_pressed)
        {
            handle_door_interaction(data);
            e_key_pressed = true;
        }
    }
    else
    {
        e_key_pressed = false;
    }
}


void	render(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (mlx_is_key_down(data->map->mlx, MLX_KEY_ESCAPE))
	{
		free_txtr(data);
		free(data->player);
		mlx_close_window(data->map->mlx);
		return ;
	}
	ft_keys(data);
	render_all(data);
}
