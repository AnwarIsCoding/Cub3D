/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 00:21:52 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/15 18:28:21 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include "libft_garb_collect/libft.h"

# define BUFFER_SIZE 1024
# define MX 2147483647
# define MN -2147483648
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <ctype.h>
# include <errno.h>
# include <stdbool.h>

typedef struct s_state
{
	int		k;
	int		p;
	int		map_cnt;
}	t_state;

typedef struct s_info {
	int			floor[3];
	int			ceiling[3];
	bool		check[7];
	char		**map;
	char		*north_path;
	char		*south_path;
	char		*west_path;
	char		*east_path;
	char		*door;
	float		x;
	float		y;
	int			rows;
	int			cols;
	char		headed;
}	t_info;

//parser
int		is_walkable(char c);
int		map_checker(t_info *config);
int		is_walkable(char c);
int		is_outside(char **map, int i, int j);
int		is_line_empty(char *s);
int		parse_map_line(char *line, t_info *config, t_state *st, t_garbage **g);
int		parse_color(char *str, int color[3]);
int		parser(int ac, char **av, t_info *config, t_garbage **g);
char	*skipst(char *s);
int		read_cub_file(int fd, t_info *config, t_garbage **g);
char	**add_map_line(char **map, char *line, int *count, t_garbage **garb);
int		get_texture_index(char *line);
int		check_boundaries(t_info *config);
int		all_chars(char **map, t_info *config);
//config
int		config_check(t_info *config);

//utils
int		has_cub(char *s);

char	*get_next_line(int fd, t_garbage **g);

#endif