/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:31:36 by amaliari          #+#    #+#             */
/*   Updated: 2025/10/29 13:09:57 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"




void	cast_ray(float ray_angle, int strip_id, t_game *cub, t_ray *rays)
{
	// float x_intercept;
	// float y_intercept;
	t_intercept intercept;
	t_hori *hori;
	t_vert *vert;
	t_step *steps;

	steps = malloc(sizeof(t_step));
	identifing_ray_facing(ray_angle, strip_id, rays);
	for_horizontal_intersection(&intercept, rays, strip_id, cub);
	horizontal_steps(steps, rays, strip_id);
	hori = horizontal_part(intercept, *steps, cub, strip_id);
	for_vertical_intersection(&intercept, rays, strip_id, cub);
	vertical_steps(steps, rays, strip_id);
	vert = vertical_part(intercept, *steps, cub, strip_id);
	smallest_distance_adaptation(*hori, *vert, rays, strip_id);
	free(steps);
	free(hori);
	free(vert);
}

void    cast_all_rays(t_game *cub)
{
    float	ray_angle;
	int		strip_id;

	strip_id = 0;
	ray_angle = cub->player->rotation_angle - (FOV_ANGLE / 2);
	while (strip_id < NUM_RAYS)
	{
		ray_angle = normalize_angle(ray_angle);
		cast_ray(ray_angle, strip_id, cub, cub->rays);
		ray_angle += FOV_ANGLE / NUM_RAYS;
		strip_id++;
	}
}

void draw_wall_with_ceiling_floor(t_game *cub, int strip_id, float wall_height, int color)
{
    int start_x;
    int end_x;
    int wall_top;
    int wall_bottom;
	int y;

	start_x = strip_id * (floor(STRIP_WIDTH) + 1);
	end_x = start_x + (floor(STRIP_WIDTH) + 1);
	wall_top = (HEIGHT / 2) - (floor(wall_height) / 2);
	wall_bottom = (HEIGHT / 2) + (floor(wall_height) / 2);
    while (start_x < end_x)
    {
		y = 0;
        while (y < wall_top)
        {
            put_pixel(&cub->img, start_x, y, 0);  // Sky blue
            y++;
        }
        while (y < wall_bottom)
        {
            put_pixel(&cub->img, start_x, y, 0xFFFFFF);
            y++;
        }
        while (y < HEIGHT)
        {
            put_pixel(&cub->img, start_x, y, 0);  // Forest green
            y++;
        }
        start_x++;
    }
}


void	render_the_rays(t_game *cub)
{
	int		i;
	float	wall_height;
	float	corrected_distance;

	i = 0;
	cast_all_rays(cub);
	while (i < NUM_RAYS)
	{
		corrected_distance = cub->rays[i].distance 
				* cos(cub->rays[i].ray_angle - cub->player->rotation_angle);
		wall_height = (TILE_SIZE * HEIGHT) / corrected_distance;
		// draw_line(cub, cub->player->x, cub->player->y, cub->rays[i].wall_hit_x, cub->rays[i].wall_hit_y);
		draw_wall_with_ceiling_floor(cub, i, wall_height, 0xFFFF0000);
		i++;
	}
}