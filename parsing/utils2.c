/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 17:00:18 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/16 11:08:54 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	set_texture_path(t_info *config, int i, char *path)
{
	if (i == 0)
		config->north_path = path;
	else if (i == 1)
		config->south_path = path;
	else if (i == 2)
		config->west_path = path;
	else if (i == 3)
		config->east_path = path;
	else if (i == 4)
		config->door = path;
}

char    *texture(char *line)
{
    int i;

    i = ft_strlen(line) - 1;
    while (i >= 0 && line[i] == ' ')
        i--;
    line[i + 1] = '\0';
    return (line);
}

static int	parse_texture_line(char *line, t_info *config, t_garbage **g)
{
	int		i;
	char	*path;

	i = get_texture_index(line);
	if (i == -1 || config->check[i])
		return (1);
	line = skipst(line+2);
	path = ft_strdup_g(texture(line), g);
	if (!path)
		return (1);
	set_texture_path(config, i, path);
	config->check[i] = true;
	return (0);
}

static int	parse_color_line(char *line, t_info *config)
{
	if (line[0] == 'F')
	{
		if (config->check[5])
			return (1);
		if (parse_color(skipst(line + 1), config->floor))
			return (1);
		config->check[5] = true;
	}
	else if (line[0] == 'C')
	{
		if (config->check[6])
			return (1);
		if (parse_color(skipst(line + 1), config->ceiling))
			return (1);
		config->check[6] = true;
	}
	else
		return (1);
	return (0);
}

static int	parse_line(char *line, t_info *config, t_state *st, t_garbage **g)
{
	line = skipst(line);
	st->p = 1;
	if ((!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
			|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
			|| !ft_strncmp(line, "DO", 2))
		&& (st->k >= 0 && st->k <= 4))
	{
		if (parse_texture_line(line, config, g))
			return (1);
		st->k++;
	}
	else if ((line[0] == 'F' || line[0] == 'C') && (st->k >= 5 && st->k <= 6))
	{
		if (parse_color_line(line, config))
			return (1);
		st->k++;
	}
	else if (st->k >= 7)
	{
		parse_map_line(line, config, st, g);
		st->p = 0;
	}
	return (0);
}

int	read_cub_file(int fd, t_info *config, t_garbage **g)
{
	char	*line;
	t_state	st;

	st.k = 0;
	st.p = 0;
	st.map_cnt = 0;
	line = get_next_line(fd, g);
	while (line != NULL)
	{
		if (parse_line(line, config, &st, g))
			return (1);
		line = get_next_line(fd, g);
	}
	return (0);
}
