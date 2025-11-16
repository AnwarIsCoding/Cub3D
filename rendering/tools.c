/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:58:38 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/16 22:56:13 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	normalize_angle(float angle)
{
	angle = fmod(angle, 2 * PI);
	if (angle < 0)
		angle += 2 * PI;
	return (angle);
}

void	put_pixel(t_img *img, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT)
		return ;
	dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

bool	wall_collision(t_game *cub, float player_x, float player_y)
{
	int	grid_x;
	int	grid_y;

	grid_x = floor(player_x) / (TILE_SIZE);
	grid_y = floor(player_y) / (TILE_SIZE);
	if (grid_x < 0 || grid_x >= cub->info->cols || grid_y < 0
		|| grid_y >= cub->info->rows)
		return (true);
	if (cub->info->map[grid_y] && (cub->info->map[grid_y][grid_x] == '1'
		|| (cub->info->map[grid_y][grid_x] == 'D' && cub->door_render)))
		return (true);
	return (false);
}

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*str;
	size_t			i;

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
	ft_memset(cub->img.addr, 0, HEIGHT * cub->img.line_length);
	render_the_rays(cub);
	mlx_put_image_to_window(cub->mlx_ptr, cub->mlx_win, cub->img.img, 0, 0);
}
