/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/09 15:20:47 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/09 18:04:17 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	is_invalid_boundary(char **map, int i, int j)
{
	if (i == 0 || j == 0 || !map[i + 1] || !map[i][j + 1])
		return (1);
	if (j >= (int)strlen(map[i - 1]) || is_outside(map, i - 1, j))
		return (1);
	if (j >= (int)strlen(map[i + 1]) || is_outside(map, i + 1, j))
		return (1);
	if (is_outside(map, i, j - 1) || is_outside(map, i, j + 1))
		return (1);
	return (0);
}

static int	validate_map_tiles(char **map, int *last_num_cols)
{
	int	i;
	int	j;

	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (is_walkable(map[i][j]) && is_invalid_boundary(map, i, j))
			{
				printf("Error\nmap not closed\n");
				return (1);
			}
			j++;
			if (*last_num_cols < j)
				*last_num_cols = j;
		}
		i++;
	}
	return (0);
}

int	check_boundaries(t_info *config)
{
	int		last_num_cols;

	last_num_cols = 0;
	if (validate_map_tiles(config->map, &last_num_cols))
		return (1);
	config->rows = 0;
	while (config->map[config->rows])
		config->rows++;
	config->cols = last_num_cols;
	return (0);
}
