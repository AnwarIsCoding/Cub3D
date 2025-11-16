/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_the_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 15:35:29 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/11 10:09:46 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	draw_tile(t_game *cub, int start_x, int start_y, t_mini_map mini_map)
{
	int	y;
	int	x;

	y = start_y;
	while (y < start_y + mini_map.tile_size)
	{
		x = start_x;
		while (x < start_x + mini_map.tile_size)
		{
			put_pixel(&cub->img, x, y, mini_map.color);
			x++;
		}
		y++;
	}
}

void	draw_player_on_minimap(t_game *cub, int tile_size)
{
	int	center_x;
	int	center_y;
	int	size;
	int	x;
	int	y;

	center_x = MINIMAP_SIZE / 2;
	center_y = MINIMAP_SIZE / 2;
	size = tile_size;
	if (size < 3)
		size = 3;
	if (size > 15)
		size = 15;
	y = center_y - size / 2;
	while (y <= center_y + size / 2)
	{
		x = center_x - size / 2;
		while (x <= center_x + size / 2)
		{
			put_pixel(&cub->img, x, y, 0xFF0000);
			x++;
		}
		y++;
	}
}

void	mini_map_initialization(t_game *cub, t_mini_map *mini_map)
{
	get_map_dimensions(cub, &mini_map->width, &mini_map->height);
	mini_map->tile_size = MINIMAP_SIZE / MINIMAP_VIEW;
	mini_map->player_tile_x = (int)(cub->player->x / TILE_SIZE);
	mini_map->player_tile_y = (int)(cub->player->y / TILE_SIZE);
	mini_map->view_radius = MINIMAP_VIEW / 2;
	mini_map->start_x = mini_map->player_tile_x - mini_map->view_radius;
	mini_map->start_y = mini_map->player_tile_y - mini_map->view_radius;
}

int	getting_tile_color(char tile)
{
	if (tile == '1')
		return (0xFFFFFF);
	else if (tile == '0')
		return (0x000000);
	else
		return (0x777777);
}

void	draw_minimap(t_game *cub)
{
	t_mini_map	mini_map;
	int			y;
	int			x;

	y = 0;
	mini_map_initialization(cub, &mini_map);
	while (y < MINIMAP_VIEW)
	{
		x = 0;
		while (x < MINIMAP_VIEW)
		{
			mini_map.map_x = mini_map.start_x + x;
			mini_map.map_y = mini_map.start_y + y;
			mini_map.color = 0x444444;
			if (mini_map.map_x >= 0 && mini_map.map_y >= 0 && mini_map.map_x
				< mini_map.width && mini_map.map_y < mini_map.height)
				mini_map.color = getting_tile_color
					(cub->info->map[mini_map.map_y][mini_map.map_x]);
			draw_tile(cub, x * mini_map.tile_size,
				y * mini_map.tile_size, mini_map);
			x++;
		}
		y++;
	}
	draw_player_on_minimap(cub, mini_map.tile_size);
}
