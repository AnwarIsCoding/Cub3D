/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:58:38 by amaliari          #+#    #+#             */
/*   Updated: 2025/10/28 14:52:26 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    setup_game(t_player *player)
{
    player->x = 0;
    player->y = 0;
}

float normalize_angle(float angle)
{
    angle = fmod(angle, 2 * PI);
    if (angle < 0)
        angle += 2 * PI;
    return angle;
}

void    update(t_player *player)
{
    if (player->x < 0)
        player->x = 0;
    if (player->y < 0)
        player->y = 0;
    else if (player->x >= WIDTH - 20)
        player->x = WIDTH - 20;
    else if (player->x >= HEIGHT - 20)
        player->x = HEIGHT - 20;
}

void	put_pixel(t_img *img, int x, int y, int color)
{
    char	*dst;
    
    // Bounds check (optional but safe)
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
        return ;

    dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int    cleanup_and_exit(t_game *cub)
{
    mlx_destroy_image(cub->mlx_ptr, cub->img.img);
    mlx_destroy_window(cub->mlx_ptr, cub->mlx_win);
    exit(0);
}

bool wall_collision(t_game *cub, float player_x, float player_y)
{
	int	grid_x;
	int	grid_y;
	
    grid_x = floor(player_x) / (TILE_SIZE);
    grid_y = floor(player_y) / (TILE_SIZE);

    // printf("cub->map[%d][%d] = %c\n", grid_y, grid_x, cub->map[grid_y][grid_x]);
    if (cub->game_info->map[grid_y][grid_x] == '1')
    {
        return (true);
    }
    if (grid_x < 0 || grid_x >= cub->game_info->num_rows|| grid_y < 0
        || grid_y >= cub->game_info->num_rows)
        {
            return (true);
            //  printf("grid condition grid_x == 0 || grid_x >= MAP_NUM_COLS || ...\n");
        }
    return (false);
}

float   distance_between_points(float x1, float y1, float x2, float y2)
{
    return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

void    draw_line(t_game *cub, int tile_size, float end_x, float end_y)
{

    float   steps;
    float   x_inc;
    float   y_inc;
    t_line  line;
    int     i;

    line.dx = end_x - (int)cub->player->x * tile_size / TILE_SIZE;
    line.dy = end_y - (int)cub->player->y * tile_size / TILE_SIZE; 
    if (fabs(line.dx) > fabs(line.dy))
        steps = fabs(line.dx);
    else
        steps = fabs(line.dy);
    x_inc = line.dx / steps;
    y_inc = line.dy / steps;
    line.x = (int)cub->player->x * tile_size / TILE_SIZE;
    line.y = (int)cub->player->y * tile_size / TILE_SIZE;
    i = 0;
    while (i <= steps)
    {
        put_pixel(&cub->img, line.x, line.y, 0xFFFFFF);
        line.x += x_inc;
        line.y += y_inc;
        i++;
    }
}

void    *ft_memset(void *b, int c, size_t len)
{
        unsigned char   *str;
        size_t                  i;

        str = (unsigned char *)b;
        i = 0;
        while (i < len)
        {
                str[i] = (unsigned char)c;
                i++;
        }
        return (b);
}

void	render(t_game *cub)
{
    ft_memset(cub->img.addr, 0, HEIGHT * cub->img.line_length); //ft_memset
    render_the_rays(cub);
    rendering_the_player(cub);
    mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_win, cub->img.img, 0, 0);
}



// ray casting functions tools
