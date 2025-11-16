/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/29 23:55:43 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/16 16:45:39 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	load_texture(t_game *cub, t_texture *texture, char *text_path)
{
	texture->img = mlx_xpm_file_to_image(cub->mlx_ptr, text_path,
			&texture->width, &texture->height);
	if (!texture->img)
	{
		printf("Error\nFailed to load texture: %s\n", text_path);
		garbage_clear(cub->garb);
		exit(1);
	}
	texture->addr = mlx_get_data_addr(texture->img, &texture->bits_per_pixel,
			&texture->line_length, &texture->endian);
}

int	get_texture_color(t_texture *texture, int tex_x, int tex_y)
{
	char	*pixel;

	if (tex_x < 0 || tex_x >= texture->width
		|| tex_y < 0 || tex_y >= texture->height)
		return (0x000000);
	pixel = texture->addr + (tex_y * texture->line_length
			+ tex_x * (texture->bits_per_pixel / 8));
	return (*(int *)pixel);
}

void	put_texture_preloaded(t_game *cub, int strip_id,
	float wall_height, t_drawing draw)
{
	float	wall_x;
	float	wall_progress;
	int		color;

	if (!draw.text)
		return ;
	if (cub->rays[strip_id].was_hit_vertical)
		wall_x = cub->rays[strip_id].wall_hit_y;
	else
		wall_x = cub->rays[strip_id].wall_hit_x;
	wall_x = fmod(wall_x, TILE_SIZE) / TILE_SIZE;
	draw.text->x = (int)(wall_x * draw.text->width);
	if (draw.text->x >= draw.text->width)
		draw.text->x = draw.text->width - 1;
	wall_progress = ((float)draw.y - draw.wall_top) / wall_height;
	if (wall_progress < 0.0f)
		wall_progress = 0.0f;
	if (wall_progress > 1.0f)
		wall_progress = 1.0f;
	draw.text->y = (int)(wall_progress * (float)draw.text->height);
	if (draw.text->y >= draw.text->height)
		draw.text->y = draw.text->height - 1;
	color = get_texture_color(draw.text, draw.text->x, draw.text->y);
	put_pixel(&cub->img, draw.start_x, draw.y, color);
}
