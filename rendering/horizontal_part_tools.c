/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal_part_tools.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:08:15 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/16 13:11:12 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	for_horizontal_intersection(t_intercept *intercept,
		t_ray *rays, int strip_id, t_game *cub)
{
	intercept->y_intercept = floor(cub->player->y / TILE_SIZE) * TILE_SIZE;
	if (rays[strip_id].is_ray_facing_down)
		intercept->y_intercept += TILE_SIZE;
	intercept->x_intercept = cub->player->x
		+ (intercept->y_intercept - cub->player->y)
		/ tan(rays[strip_id].ray_angle);
}

void	horizontal_steps(t_step *steps, t_ray *rays, int strip_id)
{
	steps->y_step = TILE_SIZE;
	if (rays[strip_id].is_ray_facing_up)
		steps->y_step *= -1;
	steps->x_step = TILE_SIZE / tan(rays[strip_id].ray_angle);
	if (rays[strip_id].is_ray_facing_left && steps->x_step > 0)
		steps->x_step *= -1;
	if (rays[strip_id].is_ray_facing_right && steps->x_step < 0)
		steps->x_step *= -1;
}

void	initializing_horizontal_part(t_hori *hori,
		float x_intercept, float y_intercept)
{
	hori->hori_wall_hit = false;
	hori->next_hori_touch_x = x_intercept;
	hori->next_hori_touch_y = y_intercept;
}

int	affecting_to_hori_struct(t_hori *hori,
		t_game *cub, float x_to_check, float y_to_check)
{
	int		grid_x;
	int		grid_y;

	grid_y = (int)floor(y_to_check / TILE_SIZE);
	grid_x = (int)floor(x_to_check / TILE_SIZE);
	if (grid_x < 0 || grid_x >= cub->info->cols || grid_y < 0
		|| grid_y >= cub->info->rows)
		return (1);
	if (wall_collision(cub, x_to_check, y_to_check))
	{
		hori->hori_wall_hit_x = hori->next_hori_touch_x;
		hori->hori_wall_hit_y = hori->next_hori_touch_y;
		hori->hori_wall_content = cub->info->map[grid_y][grid_x];
		hori->hori_wall_hit = true;
		return (1);
	}
	return (0);
}

void	find_horizontal_wall_hit(t_hori *hori, t_step steps,
		t_game *cub, int strip_id)
{
	float	x_to_check;
	float	y_to_check;

	while (hori->next_hori_touch_x >= 0 && hori->next_hori_touch_x
		< cub->info->cols * TILE_SIZE
		&& hori->next_hori_touch_y >= 0 && hori->next_hori_touch_y
		< cub->info->rows * TILE_SIZE
	)
	{
		x_to_check = hori->next_hori_touch_x;
		y_to_check = hori->next_hori_touch_y;
		if (cub->rays[strip_id].is_ray_facing_up)
			y_to_check -= 1;
		if (affecting_to_hori_struct(hori, cub, x_to_check, y_to_check))
			break ;
		hori->next_hori_touch_x += steps.x_step;
		hori->next_hori_touch_y += steps.y_step;
	}
}
