/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaliari <amaliari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 22:31:17 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/16 11:06:38 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_map_line(char *line)
{
	int	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	if (line[i] == '1' || line[i] == '0')
		return (1);
	return (0);
}

int	parse_color(char *str, int color[3])
{
	int		i;
	char	*ptr;

	ptr = str;
	i = 0;
	while (*ptr)
	{
		while (*ptr == ' ' || *ptr == ',')
			ptr++;
		if (i >= 3)
			return (1);
		color[i++] = ft_atoi(ptr);
		while (*ptr >= '0' && *ptr <= '9')
			ptr++;
	}
	return (0);
}

void	init_struct(t_info *config)
{
	int	i;

	i = 7;
	config->map = NULL;
	config->door = NULL;
	config->north_path = NULL;
	config->south_path = NULL;
	config->west_path = NULL;
	config->east_path = NULL;
	config->ceiling[0] = 1e9;
	config->floor[0] = 1e9;
	config->headed = '0';
	config->x = 0;
	config->y = 0;
	while (i--)
		config->check[i] = false;
}

char	*skipst(char *s)
{
	int	i;

	i = 0;
	while (s[i] == ' ' || s[i] == '\t')
		i++;
	return (s + i);
}

int	parser(int ac, char **av, t_info *config, t_garbage **g)
{
	int	fd;

	if (ac < 2)
		return (printf("Error\nneed a .cub file\n"), 1);
	if (!has_cub(av[1]))
		return (printf("Error\nfile must end with .cub\n"), 1);
	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (perror("open"), 1);
	init_struct(config);
	if (read_cub_file(fd, config, g))
		return (close(fd), 1);
	close(fd);
	return (0);
}
