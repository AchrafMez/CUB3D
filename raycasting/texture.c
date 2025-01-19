#include "../cub3.h"

void load_tex(t_data *data)
{
	t_map *map = data->map;	
	map->textures[0] = mlx_load_png(map->SO);
	map->textures[1] = mlx_load_png(map->NO);
	map->textures[2] = mlx_load_png(map->WE);
	map->textures[3] = mlx_load_png(map->EA);
	if(!map->textures[0] || !map->textures[1] || !map->textures[2] || !map->textures[3] )
		exit(1);
}

float get_tex_x(t_ray *ray, mlx_texture_t *tex)
{
    float tex_x;
    float tex_width = (float)tex->width;
    
    if (ray->was_vert)
    {
        tex_x = ray->wall_hit_Y;
        tex_x = fmod(tex_x, TILE_SIZE);

        if (tex_x < 0)
            tex_x += TILE_SIZE;
        tex_x = (tex_x * tex_width) / TILE_SIZE;
        if (ray->ray_facing_left)
            tex_x = tex_width - tex_x - 1;
    }
    else
    {
        tex_x = ray->wall_hit_X;
        tex_x = fmod(tex_x, TILE_SIZE);
        if (tex_x < 0)
            tex_x += TILE_SIZE;
        tex_x = (tex_x * tex_width) / TILE_SIZE;

        if (ray->ray_facing_up)
            tex_x = tex_width - tex_x - 1;
    }
    

    if (tex_x >= tex_width)
        tex_x = tex_width - 1;
    if (tex_x < 0)
        tex_x = 0;
        
    return tex_x;
}
void draw_tex(int i, int wall_top, int wall_height, 
                        float tex_x, mlx_texture_t *tex, t_data *data)
{
    int draw_start = wall_top;
    int draw_end = wall_top + wall_height;
    
    if (draw_start < 0)
        draw_start = 0;
    if (draw_end >= WIN_HEIGHT)
        draw_end = WIN_HEIGHT - 1;

    int tex_x_pixel = (int)tex_x;
    if (tex_x_pixel < 0)
        tex_x_pixel = 0;
    else if ((uint32_t)tex_x_pixel >= tex->width)
        tex_x_pixel = tex->width - 1;
    
    while (draw_start <= draw_end)
    {
        float tex_y_ratio = (float)(draw_start - wall_top) / wall_height;
        int tex_y_pixel = (int)(tex_y_ratio * tex->height);
        
        if (tex_y_pixel < 0)
            tex_y_pixel = 0;
        else if ((uint16_t)tex_y_pixel >= tex->height)
            tex_y_pixel = tex->height - 1;
        
        int tex_pos = (tex_y_pixel * tex->width + tex_x_pixel) * tex->bytes_per_pixel;
        uint32_t color;
        
        // if (tex->bytes_per_pixel == 4)
        // {
            color = (tex->pixels[tex_pos] << 24) |  (tex->pixels[tex_pos + 1] << 16) | (tex->pixels[tex_pos + 2] << 8) |  tex->pixels[tex_pos + 3];
        // }
        // else
        // {
            // color = (tex->pixels[tex_pos] << 16) |    (tex->pixels[tex_pos + 1] << 8) | tex->pixels[tex_pos + 2] | 0xFF000000;
        // }
        
        if (i >= 0 && i < WIN_WIDTH && draw_start >= 0 && draw_start < WIN_HEIGHT)
            mlx_put_pixel(data->map->img, i, draw_start, color);
        draw_start++;
    }
}

void render_walls(t_ray **rays, t_data *data)
{
    int i = -1;
    float proj_plane_dist = (WIN_WIDTH / 2) / tan(data->player->FOV / 2);
    
    clear_image(data->map->img);
    while (++i < WIN_WIDTH)
    {
        t_ray *ray = rays[i];
        float correct_dist = ray->distance * cos(ray->ray_angle - data->player->rotation_angle);
        if (correct_dist <= 1.0f)
            correct_dist = 1.0f;
            
        int wall_height = (int)((float)TILE_SIZE / correct_dist * proj_plane_dist);
        int wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
        
        mlx_texture_t *tex;
        if (ray->was_vert) {
            if (ray->ray_facing_left)
                tex = data->map->textures[2];
            else
                tex = data->map->textures[3];
        } else {
            if (ray->ray_facing_up)
                tex = data->map->textures[0];
            else
                tex = data->map->textures[1];
        }
            
        float tex_x = get_tex_x(ray, tex);
        draw_tex(i, wall_top, wall_height, tex_x, tex, data);
    }
}
