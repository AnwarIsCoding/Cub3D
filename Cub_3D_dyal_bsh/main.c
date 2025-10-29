/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:24:39 by amaliari          #+#    #+#             */
/*   Updated: 2025/10/28 14:39:08 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include  "parsing/wolfnstein/cube.h"

int		game_loop(t_game *cub)
{
	// update(cub->player);
	render(cub);
	draw_minimap(cub);
	mlx_mouse_hide(cub->mlx_ptr, cub->mlx_win);
	// draw_gps_minimap(cub);	
	return (0);
}


int	initialize_window(t_game *cub)
{
	// cub->map = malloc(MAP_NUM_COLS * MAP_NUM_ROWS);
    // cub->map = map;
	cub->player = malloc(sizeof(t_player));
	if (!cub->player)
		return (0);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		return (0);
	cub->mlx_win = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	cub->img.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img.addr = mlx_get_data_addr(cub->img.img,
			&cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);
	player_init(cub, cub->player);
	if (!mlx_hook(cub->mlx_win, 2, 1L<<0, process_events, cub))
		return (0);
	if (!mlx_hook(cub->mlx_win, 17, 0, cleanup_and_exit, cub))
		return (0);
	if (!mlx_hook(cub->mlx_win, 6, 1L<<6, process_mouse, cub))
		return (0);
	if (!mlx_loop_hook(cub->mlx_ptr, game_loop, cub))
		return (0);
	mlx_mouse_move(cub->mlx_ptr, cub->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_loop(cub->mlx_ptr);
	return (1); // add protections later ===> return 0 in each
}

int	main(int ac, char **av)
{
	t_game		cub;
	t_info	config;
	
	if (ac != 2)
		return (printf("need 2 args !\n"), 1);
	if (parser(ac, av, &config))
		return (printf("Error\ninput isnt compatible !\n"), 1);
	if (config_check(&config))
		return (1);
	cub.game_info = &config;
	if (!initialize_window(&cub))
		return (1);
	mlx_destroy_window(cub.mlx_ptr, cub.mlx_win);
	return (0);
}
