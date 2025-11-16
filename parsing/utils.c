/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 02:37:01 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/16 11:07:41 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	get_texture_index(char *line)
{
	if (!ft_strncmp(line, "NO", 2))
		return (0);
	else if (!ft_strncmp(line, "SO", 2))
		return (1);
	else if (!ft_strncmp(line, "WE", 2))
		return (2);
	else if (!ft_strncmp(line, "EA", 2))
		return (3);
	else if (!ft_strncmp(line, "DO", 2))
		return (4);
	return (-1);
}

char	**add_map_line(char **map, char *line, int *count, t_garbage **garb)
{
	char	**new_map;
	int		i;

	i = 0;
	new_map = ft_malloc(sizeof(char *) * (*count + 2), garb);
	if (!new_map)
		return (NULL);
	while (i < *count)
	{
		new_map[i] = map[i];
		i++;
	}
	new_map[*count] = ft_strdup_g(line, garb);
	new_map[*count + 1] = NULL;
	(*count)++;
	return (new_map);
}

int	parse_map_line(char *line, t_info *config, t_state *st, t_garbage **g)
{
	config->map = add_map_line(config->map, line, &st->map_cnt, g);
	return (0);
}

int	has_cub(char *s)
{
	size_t	ss;

	ss = ft_strlen(s);
	if (ss < 4)
		return (0);
	if (!ft_strcmp(".cub", s + ss - 4))
		return (1);
	return (0);
}
