/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abmahfou <abmahfou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 11:31:49 by abmahfou          #+#    #+#             */
/*   Updated: 2025/01/07 13:23:14 by abmahfou         ###   ########.fr       */
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
#define LINE_LENGTH 20

typedef struct	s_player {
	float	x;
	float	y;
	float	radius;
	int		turn_direction;
	int		walk_direction;
	float	rotation_angle;
	float	move_speed;
	float	rotation_speed;
	double	FOV;
	mlx_image_t	*pl;
	mlx_image_t	*line;
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
	int	y;
	int	x;
	int	py;
	int	px;

	y = -1;
	while (game->map[++y] != NULL)
	{
		x = -1;
		while (game->map[y][++x])
		{
			uint32_t color = ft_pixel(100,100,105,155); // Default to wall
			if (game->map[y][x] == '1')
				color = ft_pixel(55,55,55,55);
			else if (game->map[y][x] == ' ')
				color = ft_pixel(0,0,0,0);
			py = -1;
			while (++py < TILE_SIZE)
			{
				px = -1;
				while (++px < TILE_SIZE)
					mlx_put_pixel(game->image, x * TILE_SIZE + px, y * TILE_SIZE + py, color);
			}
		}
	}
}

void	draw_line(mlx_image_t *img, int x0, int y0, int x1, int y1, uint32_t color) {
	int dx;
	int dy;
	int	i;

	dx = x1- x0;
	dy = y1 - y0;
	i = -1;
	int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
	float x_inc = dx / (float)steps;
	float y_inc = dy / (float)steps;

	float x = x0;
	float y = y0;
	while (++i <= steps)
	{
		if (x >= 0 && x < img->width && y >= 0 && y < img->height)
			mlx_put_pixel(img, (int)round(x), (int)round(y), color);
		x += x_inc;
		y += y_inc;
	}
}

void update_line(t_cub *game) {
	int	y;
	int	x;

	y = 0;
	mlx_image_t *line_img = game->player->line;
	while ((uint32_t)y < line_img->height)
	{
		x = 0;
		while ((uint32_t)x < line_img->width)
		{
			mlx_put_pixel(line_img, x, y, 0x00000000);
			x++;
		}
		y++;
	}

	int x1 = game->player->pl->instances->x + cos(game->player->rotation_angle) * LINE_LENGTH;
	int y1 = game->player->pl->instances->y + sin(game->player->rotation_angle) * LINE_LENGTH;

	draw_line(line_img, game->player->pl->instances->x, game->player->pl->instances->y, x1, y1, 0xFF0000FF);
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

int	is_collision(t_cub *game, float new_X, float new_Y)
{
	if (is_WALL(game, new_X - 8, new_Y - 8) ||
		is_WALL(game, new_X + 8, new_Y - 8) ||
		is_WALL(game, new_X - 8, new_Y + 8) ||
		is_WALL(game, new_X + 8, new_Y + 8))
		return (1);
	return (0);
}

void	update_player(t_cub *game) {
	t_player *player = game->player;
	int32_t new_X;
	int32_t new_Y;

	player->rotation_angle += player->turn_direction * player->rotation_speed;

	float move_step = player->walk_direction * player->move_speed;
	new_X = player->pl->instances->x + round(cos(player->rotation_angle) * move_step);
	new_Y = player->pl->instances->y + round(sin(player->rotation_angle) * move_step);
	if (!is_collision(game, new_X, new_Y)) {
		player->pl->instances->x = new_X;
		player->pl->instances->y = new_Y;
	}
	update_line(game);
}

void	render(void *param)
{
	t_cub	*game;

	game = (t_cub *)param;
	
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
		game->player->walk_direction = 1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->player->walk_direction = -1;
	else
		game->player->walk_direction = 0;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->turn_direction = 1;
	else if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->turn_direction = -1;
	else
		game->player->turn_direction = 0;
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
		"100000000000101",
		"100001000000101",
		"111100000010101",
		"100000000010101",
		"100000001111101",
		"10000N000000001",
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
	mlx_image_to_window(game.mlx, game.image, 0, 0);
	render_map(&game);
	mlx_image_to_window(game.mlx, pl.pl, pl.x + TILE_SIZE / 3, pl.y + TILE_SIZE / 3);
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			mlx_put_pixel(pl.pl, x, y, ft_pixel(255, 0, 0, 255));
		}
	}
	pl.line = mlx_new_image(game.mlx, game.win_width * TILE_SIZE, game.win_height * TILE_SIZE);
	mlx_image_to_window(game.mlx, pl.line, 0, 0);

	mlx_loop_hook(game.mlx, render, &game);
	mlx_loop(game.mlx);
	mlx_delete_image(game.mlx, game.image);
	mlx_delete_image(game.mlx, pl.line);
	mlx_terminate(game.mlx);
	return EXIT_SUCCESS;
}
