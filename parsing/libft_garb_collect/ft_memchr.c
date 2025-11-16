/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:07:01 by monabati          #+#    #+#             */
/*   Updated: 2024/10/26 19:52:05 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	size_t			i;
	unsigned char	x;

	tmp = (unsigned char *) s;
	x = (unsigned char) c;
	i = 0;
	while (i < n)
	{
		if (tmp[i] == x)
			return ((void *) &tmp[i]);
		i++;
	}
	return (NULL);
}
