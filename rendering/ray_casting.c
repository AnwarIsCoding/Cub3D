/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_casting.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 09:31:36 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/16 13:20:15 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	cast_ray(float ray_angle, int strip_id, t_game *cub, t_ray *rays)
{
	t_intercept	intercept;
	t_hori		*hori;
	t_vert		*vert;
	t_step		*steps;

	cub->door_render = false;
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

void	cast_all_rays(t_game *cub)
{
	float	ray_angle;
	int		strip_id;

	strip_id = 0;
	ray_angle = cub->player->rotation_angle - (degres_to_rad(FOV_ANGLE) / 2);
	while (strip_id < NUM_RAYS)
	{
		ray_angle = normalize_angle(ray_angle);
		cast_ray(ray_angle, strip_id, cub, cub->rays);
		ray_angle += degres_to_rad(FOV_ANGLE) / NUM_RAYS;
		strip_id++;
	}
}

t_texture	*applying_texture(t_game *cub, int strip_id)
{
	t_texture	*text;

	text = NULL;
	if (cub->rays[strip_id].wall_hit_content == '1')
	{
		if (cub->rays[strip_id].was_hit_vertical)
		{
			if (cub->rays[strip_id].is_ray_facing_right)
				text = cub->tex_we;
			else
				text = cub->tex_ea;
		}
		else
		{
			if (cub->rays[strip_id].is_ray_facing_down)
				text = cub->tex_no;
			else
				text = cub->tex_so;
		}
		return (text);
	}
	else if (cub->rays[strip_id].wall_hit_content == 'D')
		text = cub->door;
	return (text);
}

void	draw_wall_with_ceiling_floor(t_game *cub,
	int strip_id, float wall_height)
{
	t_drawing	draw;

	draw.start_x = strip_id;
	draw.end_x = (strip_id + 1);
	if (draw.start_x >= WIDTH)
		return ;
	if (draw.end_x > WIDTH)
		draw.end_x = WIDTH;
	draw.wall_top = (HEIGHT / 2.0f) - (floor(wall_height) / 2.0f);
	draw.wall_bottom = (HEIGHT / 2) + (floor(wall_height) / 2);
	draw.text = applying_texture(cub, strip_id);
	while (draw.start_x < draw.end_x)
	{
		draw.y = 0;
		while (draw.y++ < (int)draw.wall_top)
			put_pixel(&cub->img, draw.start_x, draw.y,
				int_to_hex(cub->info->ceiling));
		while (draw.y++ < draw.wall_bottom)
			put_texture_preloaded(cub, strip_id, wall_height,
				draw);
		while (draw.y++ < HEIGHT)
			put_pixel(&cub->img, draw.start_x, draw.y,
				int_to_hex(cub->info->floor));
		draw.start_x++;
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
		draw_wall_with_ceiling_floor(cub, i, wall_height);
		i++;
	}
}
