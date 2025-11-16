/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 09:24:39 by amaliari          #+#    #+#             */
/*   Updated: 2025/11/16 22:19:09 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	game_loop(t_game *cub)
{
	render(cub);
	draw_minimap(cub);
	mlx_mouse_hide(cub->mlx_ptr, cub->mlx_win);
	return (0);
}

int	init_textures(t_game *cub, t_garbage **garb_list)
{
	cub->tex_no = ft_malloc(sizeof(t_texture), garb_list);
	if (!cub->tex_no)
		return (0);
	cub->tex_so = ft_malloc(sizeof(t_texture), garb_list);
	if (!cub->tex_so)
		return (0);
	cub->tex_ea = ft_malloc(sizeof(t_texture), garb_list);
	if (!cub->tex_ea)
		return (0);
	cub->tex_we = ft_malloc(sizeof(t_texture), garb_list);
	if (!cub->tex_we)
		return (0);
	cub->door = ft_malloc(sizeof(t_texture), garb_list);
	if (!cub->door)
		return (0);
	load_texture(cub, cub->tex_no, cub->info->north_path);
	load_texture(cub, cub->tex_so, cub->info->south_path);
	load_texture(cub, cub->tex_ea, cub->info->east_path);
	load_texture(cub, cub->tex_we, cub->info->west_path);
	load_texture(cub, cub->door, cub->info->door);
	return (1);
}

int	initialize_window(t_game *cub, t_garbage **garb_lst)
{
	cub->player = ft_malloc(sizeof(t_player), garb_lst);
	if (!cub->player)
		return (0);
	cub->mlx_ptr = mlx_init();
	if (!cub->mlx_ptr)
		return (0);
	cub->mlx_win = mlx_new_window(cub->mlx_ptr, WIDTH, HEIGHT, "Cub3D");
	cub->img.img = mlx_new_image(cub->mlx_ptr, WIDTH, HEIGHT);
	cub->img.addr = mlx_get_data_addr(cub->img.img,
			&cub->img.bits_per_pixel, &cub->img.line_length, &cub->img.endian);
	cub->rays = ft_malloc(sizeof(t_ray) * NUM_RAYS, garb_lst);
	if (!cub->rays)
		return (0);
	player_init(cub, cub->player);
	if (!init_textures(cub, garb_lst))
		return (0);
	mlx_hook(cub->mlx_win, 2, 1L << 0, process_events, cub);
	mlx_hook(cub->mlx_win, 17, 0, cleanup_and_exit, cub);
	mlx_hook(cub->mlx_win, 6, 1L << 6, process_mouse, cub);
	mlx_loop_hook(cub->mlx_ptr, game_loop, cub);
	mlx_mouse_move(cub->mlx_ptr, cub->mlx_win, WIDTH / 2, HEIGHT / 2);
	mlx_loop(cub->mlx_ptr);
	return (1);
}

int	main(int ac, char **av)
{
	t_info		config;
	t_garbage	*garb;
	t_game		cub;

	garb = NULL;
	if (ac != 2)
		return (printf("Error\nneed 2 args !\n"), 1);
	if (parser(ac, av, &config, &garb))
	{
		garbage_clear(&garb);
		return (printf("Error\ninput isnt compatible !\n"), 1);
	}
	if (config_check(&config))
		return (garbage_clear(&garb), 1);
	cub.info = &config;
	cub.garb = &garb;
	if (!initialize_window(&cub, &garb))
	{
		garbage_clear(&garb);
		return (1);
	}
	garbage_clear(&garb);
	return (0);
}
