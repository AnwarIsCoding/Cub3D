/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:08:03 by amaliari          #+#    #+#             */
/*   Updated: 2025/10/26 13:07:25 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	process_player_rotation(int key_press, t_game *cub)
{
	if (key_press == KEY_LEFT)
		cub->player->rotation_angle += cub->player->turn_speed;
	if (key_press == KEY_RIGHT)
		cub->player->rotation_angle -= cub->player->turn_speed;
}

void	process_player_movement(int key_press, t_game *cub, float *new_x, float *new_y)
{
	if (key_press == KEY_W)
	{
		*new_x += cos(cub->player->rotation_angle) * cub->player->move_speed;
		*new_y += sin(cub->player->rotation_angle) * cub->player->move_speed;
	}		
	else if (key_press == KEY_S)
	{
		*new_x -= cos(cub->player->rotation_angle) * cub->player->move_speed;
		*new_y -= sin(cub->player->rotation_angle) * cub->player->move_speed;    
	}
	else if (key_press == KEY_A)
	{
		*new_x += cos(cub->player->rotation_angle + PI / 2) * cub->player->move_speed;
		*new_y += sin(cub->player->rotation_angle + PI / 2) * cub->player->move_speed;
	}
	else if (key_press == KEY_D)
	{
		*new_x += cos(cub->player->rotation_angle - PI / 2) * cub->player->move_speed;
		*new_y += sin(cub->player->rotation_angle - PI / 2) * cub->player->move_speed;
	}
}

int    process_events(int key_press, t_game *cub)
{
	float	new_x;
	float	new_y;

	new_x = cub->player->x;
	new_y = cub->player->y;
	process_player_rotation(key_press, cub);
	process_player_movement(key_press, cub, &new_x, &new_y);
	if (key_press == KEY_ESC)
    {
		cleanup_and_exit(cub);
	}
	if (!wall_collision(cub, new_x, cub->player->y))
	cub->player->x = new_x;
	if (!wall_collision(cub, cub->player->x, new_y))
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