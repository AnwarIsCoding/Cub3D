/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:08:03 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/16 20:08:48 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	wall_collision_player(t_game *cub, float x, float y)
{
	int	grid_x;
	int	grid_y;
	int	tile;

	grid_x = floor(x) / (TILE_SIZE);
	grid_y = floor(y) / (TILE_SIZE);
	if (grid_x < 0 || grid_x >= cub->info->cols || grid_y < 0
		|| grid_y >= cub->info->rows)
		return (true);
	tile = cub->info->map[grid_y][grid_x];
	if (tile == '1')
		return (1);
	return (0);
}

void	process_player_rotation(int key_press, t_game *cub)
{
	if (key_press == KEY_LEFT)
		cub->player->rotation_angle += cub->player->turn_speed;
	if (key_press == KEY_RIGHT)
		cub->player->rotation_angle -= cub->player->turn_speed;
}

void	process_player_movement(int key_press, t_game *cub,
		float *new_x, float *new_y)
{
	float	angle;

	angle = cub->player->rotation_angle;
	if (key_press == KEY_W)
	{
		*new_x += cos(angle)
			* cub->player->move_speed;
		*new_y += sin(angle)
			* cub->player->move_speed;
	}		
	else if (key_press == KEY_S)
	{
		*new_x -= cos(angle) * cub->player->move_speed;
		*new_y -= sin(angle) * cub->player->move_speed;
	}
	else if (key_press == KEY_A)
	{
		*new_x += cos(angle - PI / 2) * cub->player->move_speed;
		*new_y += sin(angle - PI / 2) * cub->player->move_speed;
	}
	else if (key_press == KEY_D)
	{
		*new_x += cos(angle + PI / 2) * cub->player->move_speed;
		*new_y += sin(angle + PI / 2) * cub->player->move_speed;
	}
}

int	process_events(int key_press, t_game *cub)
{
	float	new_x;
	float	new_y;

	new_x = cub->player->x;
	new_y = cub->player->y;
	process_player_rotation(key_press, cub);
	process_player_movement(key_press, cub, &new_x, &new_y);
	if (key_press == KEY_ESC)
		cleanup_and_exit(cub);
	if (!wall_collision_player(cub, new_x, cub->player->y))
		cub->player->x = new_x;
	if (!wall_collision_player(cub, cub->player->x, new_y))
		cub->player->y = new_y;
	return (0);
}

int	process_mouse(int x, int y, t_game *cub)
{
	static int	previous_x;
	int			delta_x;

	previous_x = -1;
	(void)y;
	if (previous_x == -1)
		previous_x = WIDTH / 2;
	delta_x = x - previous_x;
	cub->player->rotation_angle -= delta_x * 0.0001;
	previous_x = x;
	return (0);
}
