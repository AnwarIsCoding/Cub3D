/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:25:00 by amaliari          #+#    #+#             */
/*   Updated: 2025/10/28 15:10:42 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
#define CUB3D_H

# include "minilibx-linux/mlx.h"
#include  "parsing/wolfnstein/cube.h"
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <math.h>
# include <stdbool.h>
# include <string.h>
# include <float.h>

// MATH
# define PI 3.1415926535
// MAP
# define TILE_SIZE 64
// # define MAP_NUM_ROWS 20
// # define MAP_NUM_COLS 20
// WINDOW
# define WIDTH 1000
# define HEIGHT 1000
// KEYS
# define KEY_ESC 65307
# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100
# define KEY_LEFT 65363
# define KEY_RIGHT 65361
// MINI_MAP
# define MINI_MAP_SCALE 0.25
// PLAYER
# define FOV_ANGLE (60 * (PI / 180)) 
// RAY-CASTING
# define NUM_RAYS 150
# define STRIP_WIDTH WIDTH / NUM_RAYS 

typedef struct s_img
{
    void	*img;         // Image pointer
    char	*addr;        // Direct access to pixel data
    int		bits_per_pixel;
    int		line_length;
    int		endian;
}	t_img; 

typedef struct s_player
{
    float   x;
    float   y;
    float   rotation_angle;
    float   move_speed;
    float   turn_speed;
    float   turn_direction;
    float   walk_direction;
}   t_player;

typedef struct s_ray
{
    float	ray_angle;
    float	wall_hit_x;
    float	wall_hit_y;
    float   distance;
    bool 	was_hit_vertical;
    bool 	was_hit_horizontal;
    bool 	is_ray_facing_up;
    bool 	is_ray_facing_down;
    bool 	is_ray_facing_left;
    bool 	is_ray_facing_right;
	int		wall_hit_content;
}   t_ray;

typedef struct  s_game
{
    void    *mlx_ptr;
    void    *mlx_win;
    char    **map;
    float   x_map;
    float   y_map;
    t_info *game_info;
    t_img   img;
    t_player *player;
    t_ray    rays[NUM_RAYS];
}   t_game;

typedef struct s_intercept
{
    float   x_intercept;
    float   y_intercept;
}   t_intercept;

typedef struct s_hori
{
    float	hori_wall_hit_x;
	float	hori_wall_hit_y;
	bool 	hori_wall_hit;
	char 	hori_wall_content;
    float	hori_hit_distance;
    float   next_hori_touch_x;
    float   next_hori_touch_y;
}   t_hori;

typedef struct s_vert
{
    float	vert_wall_hit_x;
	float	vert_wall_hit_y;
	bool 	vert_wall_hit;
	char 	vert_wall_content;
    float   vert_hit_distance;
    float   next_vert_touch_x;
    float   next_vert_touch_y;
}   t_vert;

typedef struct  s_step
{
    float   x_step;
    float   y_step;
}   t_step;

typedef struct  s_line
{
    float   dx;
    float   dy;
    float   x;
    float   y;  
}   t_line;

// tools:
void	put_pixel(t_img *img, int x, int y, int color);
int     cleanup_and_exit(t_game *cub);
float   distance_between_points(float x1, float y1, float x2, float y2);
void    draw_line(t_game *cub, int tile_size, float end_x, float end_y);
float normalize_angle(float angle);
// setup game setting 
void    setup_game(t_player *player);
// update functions
void    update(t_player *player);
void	render(t_game *cub);
// events:
int    process_events(int key_press, t_game *cub);
int	process_mouse(int x, int y, t_game *cub);
// player:
void    rendering_the_player(t_game *cub);
void    player_init(t_game *cub, t_player *player);
void    draw_player_line(t_player *player, t_game *cub);
// map
void    draw_the_map(t_game *cub);

// wall hit
bool    wall_collision(t_game *cub, float player_x, float player_y);
// ray-casting
void	render_the_rays(t_game *cub);
void    cast_all_rays(t_game *cub);
// ray-casting tools
void    identifing_ray_facing(float ray_angle, int strip_id, t_ray *rays);
void    smallest_distance_adaptation(t_hori hori, t_vert vert, t_ray *rays, int strip_id);
    //-->horizontal part tools
t_hori  *horizontal_part(t_intercept intercept, t_step steps, t_game *cub, int strip_id);
void	for_horizontal_intersection(t_intercept *intrcept, t_ray *rays, int strip_id, t_game *cub);
void	horizontal_steps(t_step *steps, t_ray *rays, int strip_id);
void    initializing_horizontal_part(t_hori *hori, float x_intercept, float y_intercept);
void	find_horizontal_wall_hit(t_hori *hori, t_step steps, t_game *cub,  int strip_id);

    //-->vertical part tools
t_vert  *vertical_part(t_intercept intercept, t_step steps, t_game *cub, int strip_id);
void    initializing_vertical_part(t_vert *vert, float x_intercept, float y_intercept);
void	vertical_steps(t_step *steps, t_ray *rays, int strip_id);
void	for_vertical_intersection(t_intercept *intercept, t_ray *rays, int strip_id, t_game *cub);
void	find_vertical_wall_hit(t_vert *vert, t_step steps, t_game *cub, int strip_id);
// bonus
void    draw_minimap(t_game *cub);
// void	draw_gps_minimap(t_game *cub);

#endif