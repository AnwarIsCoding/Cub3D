/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 19:51:49 by monabati          #+#    #+#             */
/*   Updated: 2025/11/05 05:27:17 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size, t_garbage **garb_coll)
{
	unsigned char	*tmp;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	tmp = (unsigned char *) ft_malloc(size * count, garb_coll);
	if (!tmp)
		return (NULL);
	ft_bzero(tmp, count * size);
	return (tmp);
}
