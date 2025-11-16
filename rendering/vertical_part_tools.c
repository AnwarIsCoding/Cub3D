/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical_part_tools.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 10:07:58 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/16 13:08:31 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	initializing_vertical_part(t_vert *vert,
	float x_intercept, float y_intercept)
{
	vert->vert_wall_hit = false;
	vert->next_vert_touch_x = x_intercept;
	vert->next_vert_touch_y = y_intercept;
}

void	vertical_steps(t_step *steps, t_ray *rays, int strip_id)
{
	steps->x_step = TILE_SIZE;
	if (rays[strip_id].is_ray_facing_left)
		steps->x_step *= -1;
	steps->y_step = TILE_SIZE * tan(rays[strip_id].ray_angle);
	if (rays[strip_id].is_ray_facing_up && steps->y_step > 0)
		steps->y_step *= -1;
	if (rays[strip_id].is_ray_facing_down && steps->y_step < 0)
		steps->y_step *= -1;
}

void	for_vertical_intersection(t_intercept *intercept,
	t_ray *rays, int strip_id, t_game *cub)
{
	intercept->x_intercept = floor(cub->player->x / TILE_SIZE) * TILE_SIZE;
	if (rays[strip_id].is_ray_facing_right)
		intercept->x_intercept += TILE_SIZE;
	intercept->y_intercept = cub->player->y
		+ (intercept->x_intercept - cub->player->x)
		* tan(rays[strip_id].ray_angle);
}

int	affecting_to_vert_struct(t_vert *vert, t_game *cub,
	float x_to_check, float y_to_check)
{
	int	grid_x;
	int	grid_y;

	grid_y = (int)floor(y_to_check / TILE_SIZE);
	grid_x = (int)floor(x_to_check / TILE_SIZE);
	if (grid_x < 0 || grid_x >= cub->info->cols
		|| grid_y < 0 || grid_y >= cub->info->rows)
		return (1);
	if (wall_collision(cub, x_to_check, y_to_check))
	{
		vert->vert_wall_hit_x = vert->next_vert_touch_x;
		vert->vert_wall_hit_y = vert->next_vert_touch_y;
		vert->vert_wall_content = cub->info->map[grid_y][grid_x];
		vert->vert_wall_hit = true;
		return (1);
	}
	return (0);
}

void	find_vertical_wall_hit(t_vert *vert, t_step steps,
	t_game *cub, int strip_id)
{
	float	x_to_check;
	float	y_to_check;

	while (vert->next_vert_touch_x >= 0 && vert->next_vert_touch_x
		< cub->info->cols * TILE_SIZE
		&& vert->next_vert_touch_y >= 0 && vert->next_vert_touch_y
		< cub->info->rows * TILE_SIZE)
	{
		x_to_check = vert->next_vert_touch_x;
		y_to_check = vert->next_vert_touch_y;
		if (cub->rays[strip_id].is_ray_facing_left)
			x_to_check -= 1;
		if (affecting_to_vert_struct(vert, cub, x_to_check, y_to_check))
			break ;
		vert->next_vert_touch_x += steps.x_step;
		vert->next_vert_touch_y += steps.y_step;
	}
}
