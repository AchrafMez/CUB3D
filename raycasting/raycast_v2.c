/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_v2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/01 15:57:19 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/03 19:35:34 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3.h"
#include "/Users/abmahfou/MLX42/include/MLX42/MLX42.h"

#define TILE_SIZE 32
#define MAP_NUM_ROWS 11
#define MAP_NUM_COLS 15

#define WINDOW_WIDTH (MAP_NUM_COLS * TILE_SIZE)
#define WINDOW_HEIGHT (MAP_NUM_ROWS * TILE_SIZE)

typedef struct	s_player {
	float	x;
	float	y;
	float	radius;
	int		turn_direction; // -1 for left, +1 for right
	int		walk_direction; // -1 for backward, +1 for forward
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
	mlx_image_t	*pl;
}				t_player;

typedef struct	s_game {
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_player	player;
	char		**map;
}				t_game;

void render_map(t_game *game) {
	int	i;
	int	j;
	int	x;
	int	y;

	i = -1;
    while (++i < MAP_NUM_ROWS)
	{
		j = -1;
        while (++j < MAP_NUM_COLS)
		{
            uint32_t color = (game->map[i][j] == '1') ? 0x222222FF : 0xFFFFFFFF;
			y = i * TILE_SIZE;
            while (y < (i + 1) * TILE_SIZE)
			{
				x = j * TILE_SIZE;
                while (x < (j + 1) * TILE_SIZE)
				{
                    mlx_put_pixel(game->img, x, y, color);
					x++;
                }
				y++;
            }
        }
    }
}

void render_player(t_game *game) {
	int	y;
	int	x;

	y = -game->player.radius;
	while (y <= game->player.radius)
	{
		x = -game->player.radius;
		while (x <= game->player.radius)
		{
			int px = game->player.x + x;
			int py = game->player.y + y;
			if (px >= 0 && px < WINDOW_WIDTH && py >= 0 && py < WINDOW_HEIGHT &&
				x * x + y * y <= game->player.radius * game->player.radius) {
				mlx_put_pixel(game->img, px, py, 0xFF0000FF);
			}
			x++;
		}
		y++;
	}
}

void	update_player(t_game *game) {
	t_player *player = &game->player;
	player->rotation_angle += player->turn_direction * player->rotation_speed;

	float move_step = player->walk_direction * player->move_speed;
	player->x += cos(player->rotation_angle) * move_step;
	player->y += sin(player->rotation_angle) * move_step;
}

void handle_key(mlx_key_data_t keydata, void *param) {
	t_game *game = (t_game *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
		if (keydata.key == MLX_KEY_UP)
			game->player.walk_direction = 1;
		else if (keydata.key == MLX_KEY_DOWN)
			game->player.walk_direction = -1;
		else if (keydata.key == MLX_KEY_RIGHT)
			game->player.turn_direction = 1;
		else if (keydata.key == MLX_KEY_LEFT)
			game->player.turn_direction = -1;
	} else if (keydata.action == MLX_RELEASE) {
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
			game->player.walk_direction = 0;
		else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
			game->player.turn_direction = 0;
	}
}

void clear_image(mlx_image_t *img, uint32_t color) {
	for (uint32_t y = 0; y < img->height; y++) {
		for (uint32_t x = 0; x < img->width; x++) {
			mlx_put_pixel(img, x, y, color);
		}
	}
}


// Main render loop
void render(void *param) {
	t_game *game = (t_game *)param;
	mlx_image_to_window(game->mlx, game->img, 0, 0);
	clear_image(game->img, 0x000000FF);
	update_player(game);
	render_map(game);
	render_player(game);
}

void	player_pos(t_player *player, char **map)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
			{
				player->x = j * TILE_SIZE;
				player->y = i * TILE_SIZE;
			}
			j++;
		}
		i++;
	}
}

int main(void)
{
	t_game game;

	game.map = (char *[]) {
		"111111111111111",
		"1N0000000000101",
		"100001000000101",
		"111100000010101",
		"100000000010101",
		"100000001111101",
		"100000000000001",
		"100000000000001",
		"111111000111101",
		"100000000000001",
		"111111111111111",
		NULL
	};
	game.mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "cub3D", false);
	if (!game.mlx)
		return (EXIT_FAILURE);

	game.img = mlx_new_image(game.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!game.img)
		return (EXIT_FAILURE);
	game.player.pl = mlx_new_image(game.mlx, TILE_SIZE, TILE_SIZE);

	game.player = (t_player){
		.radius = 4,
		.turn_direction = 0,
		.walk_direction = 0,
		.rotation_angle = M_PI / 2,
		.move_speed = 2.0,
		.rotation_speed = 2 * (M_PI / 180)
	};
	player_pos(&game.player, game.map);
	/* if (game.player.pl)
	{
		mlx_image_to_window(game.mlx, game.player.pl, game.player.x, game.player.y);
		for (int y = 0; y < 10; y++) {
			for (int x = 0; x < 10; x++) {
				mlx_put_pixel(game.player.pl, x, y, 0xFFFF00);
			}
		}
	} */
	mlx_key_hook(game.mlx, handle_key, &game);
	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	mlx_terminate(game.mlx);
	return (EXIT_SUCCESS);
}
