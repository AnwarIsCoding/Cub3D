/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting_tools.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 20:21:20 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/08 13:13:43 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	smallest_distance_adaptation(t_hori hori, t_vert vert,
	t_ray *rays, int strip_id)
{
	if (hori.hori_hit_distance < vert.vert_hit_distance)
	{
		rays[strip_id].distance = hori.hori_hit_distance;
		rays[strip_id].wall_hit_x = hori.hori_wall_hit_x;
		rays[strip_id].wall_hit_y = hori.hori_wall_hit_y;
		rays[strip_id].wall_hit_content = hori.hori_wall_content;
		rays[strip_id].was_hit_vertical = false;
	}
	else
	{
		rays[strip_id].distance = vert.vert_hit_distance;
		rays[strip_id].wall_hit_x = vert.vert_wall_hit_x;
		rays[strip_id].wall_hit_y = vert.vert_wall_hit_y;
		rays[strip_id].wall_hit_content = vert.vert_wall_content;
		rays[strip_id].was_hit_vertical = true;
	}
}

void	identifing_ray_facing(float ray_angle, int strip_id, t_ray *rays)
{
	rays[strip_id].is_ray_facing_down = (ray_angle > 0 && ray_angle < PI);
	rays[strip_id].is_ray_facing_up = !rays[strip_id].is_ray_facing_down;
	rays[strip_id].is_ray_facing_right = (ray_angle < 0.5 * PI
			|| ray_angle > 1.5 * PI);
	rays[strip_id].is_ray_facing_left = !rays[strip_id].is_ray_facing_right;
	rays[strip_id].ray_angle = ray_angle;
}

t_hori	*horizontal_part(t_intercept intercept,
	t_step steps, t_game *cub, int strip_id)
{
	t_hori	*hori;

	hori = malloc(sizeof(t_hori));
	initializing_horizontal_part(hori, intercept.x_intercept,
		intercept.y_intercept);
	find_horizontal_wall_hit(hori, steps, cub, strip_id);
	if (hori->hori_wall_hit)
		hori->hori_hit_distance = distance_between_points(cub->player->x,
				cub->player->y, hori->hori_wall_hit_x, hori->hori_wall_hit_y);
	else
		hori->hori_hit_distance = FLT_MAX;
	return (hori);
}

t_vert	*vertical_part(t_intercept intercept, t_step steps,
	t_game *cub, int strip_id)
{
	t_vert	*vert;

	vert = malloc(sizeof(t_vert));
	initializing_vertical_part(vert, intercept.x_intercept,
		intercept.y_intercept);
	find_vertical_wall_hit(vert, steps, cub, strip_id);
	if (vert->vert_wall_hit)
		vert->vert_hit_distance = distance_between_points(cub->player->x,
				cub->player->y, vert->vert_wall_hit_x, vert->vert_wall_hit_y);
	else
		vert->vert_hit_distance = FLT_MAX;
	return (vert);
}
