/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:23:43 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/15 18:26:04 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_line_empty(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] != ' ' && s[i] != '\t' && s[i] != '\n')
			return (0);
		i++;
	}
	return (1);
}

int	has_map_content(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '1' || s[i] == '0')
			return (1);
		i++;
	}
	return (0);
}

int	map_checker(t_info *config)
{
	int	i;
	int	in_map;
	int	j;

	in_map = 0;
	i = 0;
	while (config->map[i] && is_line_empty(config->map[i]))
		i++;
	while (config->map[i])
	{
		if (has_map_content(config->map[i]))
			in_map = 1;
		else if (in_map && is_line_empty(config->map[i]))
		{
			j = i + 1;
			while (config->map[j] && is_line_empty(config->map[j]))
				j++;
			if (config->map[j] && has_map_content(config->map[j]))
				return (printf("Error\nempty line inside map\n"), 1);
			break ;
		}
		i++;
	}
	return (0);
}

int	is_walkable(char c)
{
	return (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W'
		|| c == 'D');
}

int	is_outside(char **map, int i, int j)
{
	if (map[i][j] == ' ' || map[i][j] == '\t')
		return (1);
	return (0);
}
