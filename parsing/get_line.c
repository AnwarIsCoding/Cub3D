/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:28:31 by sabadri           #+#    #+#             */
/*   Updated: 2025/11/10 11:03:54 by amaliari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	*fill_line_buffer(int fd, char *line, char *buffer, t_garbage **g)
{
	int	b_read;

	b_read = read(fd, buffer, BUFFER_SIZE);
	while (b_read > 0)
	{
		buffer[b_read] = '\0';
		if (!line)
			line = ft_strdup_g(buffer, g);
		else
			line = ft_strjoin_g(line, buffer, g);
		if (ft_strchr(buffer, '\n'))
			break ;
		b_read = read(fd, buffer, BUFFER_SIZE);
	}
	if (b_read < 0)
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}

static char	*extract_line_g(char *line_buffer, t_garbage **g)
{
	int	i;

	i = 0;
	if (!line_buffer)
		return (NULL);
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	return (ft_substr_g(line_buffer, 0, i, g));
}

static char	*set_remainder_g(char *line_buffer, t_garbage **g)
{
	size_t	i;
	char	*remainder;

	i = 0;
	if (!line_buffer)
		return (NULL);
	while (line_buffer[i] && line_buffer[i] != '\n')
		i++;
	if (!line_buffer[i])
	{
		return (NULL);
	}
	remainder = ft_substr_g(line_buffer, i + 1, strlen(line_buffer) - i - 1, g);
	return (remainder);
}

char	*get_next_line(int fd, t_garbage **g)
{
	static char	*line_buffer;
	char		*str;
	char		*buffer;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = ft_malloc(BUFFER_SIZE + 1, g);
	if (!buffer)
		return (NULL);
	line_buffer = fill_line_buffer(fd, line_buffer, buffer, g);
	if (!line_buffer)
		return (NULL);
	str = extract_line_g(line_buffer, g);
	line_buffer = set_remainder_g(line_buffer, g);
	return (str);
}
