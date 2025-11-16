/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:55:45 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/16 13:19:40 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_init(t_game *cub, t_player *player)
{
	player->x = cub->info->x * TILE_SIZE + (TILE_SIZE / 2);
	player->y = cub->info->y * TILE_SIZE + (TILE_SIZE / 2);
	if (cub->info->headed == 'N')
		player->rotation_angle = 3 * PI / 2;
	else if (cub->info->headed == 'S')
		player->rotation_angle = PI / 2;
	else if (cub->info->headed == 'W')
		player->rotation_angle = PI;
	else
		player->rotation_angle = 0;
	player->move_speed = 30;
	player->turn_speed = 10 * (PI / 100);
}
