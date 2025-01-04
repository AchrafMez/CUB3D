/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:31:49 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/04 19:43:04 by abmahfou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3.h"
#include "/Users/abmahfou/MLX42/include/MLX42/MLX42.h"

#define TILE_SIZE 32
#define COLOR_BLACK 0x00000000
#define COLOR_WHITE 0xFFFFFFFF
#define COLOR_YELLOW 0xFFFFFF00
#define	WALL_STRIP_WIDTH 1
#define PI 3.14159265358979323846

typedef struct	s_player {
	float	x;
	float	y;
	float	radius;
	int		turn_direction; // -1 for left, +1 for right
	int		walk_direction; // -1 for backward, +1 for forward
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
	double	FOV;
	mlx_image_t	*pl;
}				t_player;

typedef struct	s_cub
{
	mlx_t		*mlx;
	mlx_image_t	*image;
	int			win_width;
	int			win_height;
	char		**map;
	t_player	*player;
}				t_cub;

int32_t ft_pixel(int32_t r, int32_t g, int32_t b, int32_t a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

void render_map(t_cub *game)
{
	for (int y = 0; game->map[y] != NULL; y++) {
		for (int x = 0; game->map[y][x] != '\0'; x++) {
			uint32_t color = ft_pixel(0,0,0,255); // Default to wall
			if (game->map[y][x] == '1')
				color = ft_pixel(255,255,255,255);
			else if (game->map[y][x] == ' ')
				color = ft_pixel(0,0,0,0);
			for (int py = 0; py < TILE_SIZE; py++) {
				for (int px = 0; px < TILE_SIZE; px++) {
					mlx_put_pixel(game->image, x * TILE_SIZE + px, y * TILE_SIZE + py, color);
				}
			}
		}
	}
}

int	is_WALL(t_cub *game, int x, int y)
{
	int	X_index;
	int	Y_index;

	Y_index = floor(y / TILE_SIZE);
	X_index = floor(x / TILE_SIZE);
	if (game->map[Y_index][X_index] == '1')
		return (1);
	return (0);
}

void	update_player(t_cub *game) {
	t_player *player = game->player;
	int32_t	new_X;
	int32_t	new_Y;

	player->rotation_angle += player->turn_direction * player->rotation_speed;

	float move_step = player->walk_direction * player->move_speed;
	new_X = player->pl->instances->x + round((cos(player->rotation_angle) * move_step) * 3);
	new_Y = player->pl->instances->y + round((sin(player->rotation_angle) * move_step) * 3);
	if (!is_WALL(game, new_X, new_Y))
	{
		player->pl->instances->x = new_X;
		player->pl->instances->y = new_Y;
	}
}

void	cast_all_rays(t_cub *game)
{
	int		column;
	float	ray_Angle;
	int		i;

	column = 0;
	i = 0;
	ray_Angle = game->player->rotation_angle - (game->player->FOV / 2);
	while (i < game->win_width)
	{
		
	}
	
}

void handle_key(mlx_key_data_t keydata, void *param) {
	t_cub *game = (t_cub *)param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(game->mlx);
	if (keydata.action == MLX_PRESS || keydata.action == MLX_REPEAT) {
		if (keydata.key == MLX_KEY_UP)
			game->player->walk_direction = 1;
		else if (keydata.key == MLX_KEY_DOWN)
			game->player->walk_direction = -1;
		else if (keydata.key == MLX_KEY_RIGHT)
			game->player->turn_direction = 1;
		else if (keydata.key == MLX_KEY_LEFT)
			game->player->turn_direction = -1;
	} else if (keydata.action == MLX_RELEASE) {
		if (keydata.key == MLX_KEY_UP || keydata.key == MLX_KEY_DOWN)
			game->player->walk_direction = 0;
		else if (keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
			game->player->turn_direction = 0;
	}
	update_player(game);
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

void	vars_init(t_cub *game, t_player *pl)
{
	game->win_width = 0;
	game->win_height = 0;
	pl->walk_direction = 0;
	pl->turn_direction = 0;
	pl->rotation_angle = PI / 2;
	pl->move_speed = 2.0;
	pl->rotation_speed = 2 * (PI / 180);
	pl->FOV = 60 * (PI / 180);
}

int	main(void)
{
	t_cub		game;
	t_player	pl;

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
	vars_init(&game, &pl);
	player_pos(&pl, game.map);
	while (game.map[0][game.win_width])
		game.win_width++;
	while (game.map[game.win_height])
		game.win_height++;

	game.mlx = mlx_init(game.win_width * TILE_SIZE, game.win_height * TILE_SIZE, "cub3D", true);
	if (!game.mlx) {
		fprintf(stderr, "Failed to initialize MLX42\n");
		return EXIT_FAILURE;
	}

	game.image = mlx_new_image(game.mlx, game.win_width * TILE_SIZE, game.win_height * TILE_SIZE);
	pl.pl = mlx_new_image(game.mlx, TILE_SIZE, TILE_SIZE);
	game.player = &pl;
	render_map(&game);
	mlx_image_to_window(game.mlx, game.image, 0, 0);
	mlx_image_to_window(game.mlx, pl.pl, pl.x + TILE_SIZE / 3, pl.y + TILE_SIZE / 3);

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			mlx_put_pixel(pl.pl, x, y, ft_pixel(255, 255, 0, 255));
		}
	}
	mlx_key_hook(game.mlx, handle_key, &game);
	// mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	mlx_delete_image(game.mlx, game.image);
	mlx_terminate(game.mlx);
	return EXIT_SUCCESS;
}
