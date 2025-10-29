/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:55:45 by amaliari          #+#    #+#             */
/*   Updated: 2025/10/29 13:10:43 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void player_init(t_game *cub, t_player *player)
{
    player->x = cub->game_info->x * TILE_SIZE + (TILE_SIZE / 2);
    player->y = cub->game_info->y * TILE_SIZE + (TILE_SIZE / 2);
    printf("player->x = %f\n",  cub->game_info->x);
    printf("player->y = %f\n", cub->game_info->y);
    if (cub->game_info->headed == 'N')
    {
        printf("N\n");
        player->rotation_angle = 3 * PI / 2;
    }
    else if (cub->game_info->headed == 'S')
    {
        player->rotation_angle = PI / 2;
        printf("S\n");
    }
    else if (cub->game_info->headed == 'W')
    {
        player->rotation_angle = PI;
        printf("W\n");
    }
    else
    {
        player->rotation_angle = 0;
        printf("ZOK\n");
    }
    // player->turn_direction = 0;
    // player->walk_direction = 0;
    // player->rotation_angle = 3 * PI / 2;
    player->move_speed = 15;
    player->turn_speed = 1 * (PI / 100);
}

void    draw_player_line(t_player *player, t_game *cub)
{
    float   end_x;
    float   end_y;
    float   start_x;
    float   start_y;
    float   dx;
    float   dy;
    int     i;

    start_x = player->x;
    start_y = player->y;
    end_x = start_x + cos(player->rotation_angle) * 40;
    end_y = start_y + sin(player->rotation_angle) * 40;
    dx = (end_x - start_x) / 40;
    dy = (end_y - start_y) / 40;
    i = 0;
    while (i <= 40)
    {
        put_pixel(&cub->img, start_x * MINI_MAP_SCALE + dx * i 
                , start_y * MINI_MAP_SCALE + dy * i, 0xFF0000);
        i++;
    }
}

void    rendering_the_player(t_game *cub)
{
    int i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			put_pixel(&cub->img, cub->player->x / MINI_MAP_SCALE * TILE_SIZE+ j
                    , cub->player->y / MINI_MAP_SCALE * TILE_SIZE+ i, 0xFF);
			j++;
		}
		i++;
	}
}