/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 22:55:46 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/16 11:05:57 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	floor_ceiling_check(t_info *config)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (config->ceiling[i] == (int)1e9
			|| config->ceiling[i] < 0
			|| config->ceiling[i] > 255)
			return (true);
		if (config->floor[i] == (int)1e9
			|| config->floor[i] < 0
			|| config->floor[i] > 255)
			return (true);
		i++;
	}
	return (false);
}

int	player_check(char** map)
{
	int	i;
	int	j;
	int	ans;

	ans = 0;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'S' || map[i][j] == 'N' || map[i][j] == 'W'
				|| map[i][j] == 'E')
				ans++;
			j++;
		}
		i++;
	}
	return (ans != 1);
}

int	config_check(t_info *config)
{
	if (!config)
		return (1);
	if (!config->north_path || !config->south_path
		|| !config->west_path || !config->east_path || !config->door)
		return (printf("Error\nmissing texture path\n"), 1);
	if (floor_ceiling_check(config))
		return (printf("Error\nfloor/ceiling [x] should be n->[0,255]\n"), 1);
	if (!config->map || !config->map[0])
		return (printf("Error\nmissing map data\n"), 1);
	if (map_checker(config))
		return (printf("Error\nmap error\n"), 1);
	if (player_check(config->map))
		return (printf("Error\nno/multiple players\n"), 1);
	if (check_boundaries(config))
		return (printf("Error\nboundaries error\n"), 1);
	if (!all_chars(config->map, config))
	{
		printf("Error\nno valid characters");
		return (1);
	}
	return (0);
}
