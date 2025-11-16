/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:07:10 by monabati          #+#    #+#             */
/*   Updated: 2024/11/09 14:57:42 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*t_src;
	unsigned char	*t_dst;
	size_t			i;

	if ((dst == NULL && src == NULL) || (dst == src))
		return (dst);
	t_src = (unsigned char *) src;
	t_dst = (unsigned char *) dst;
	i = 0;
	while (i < n)
	{
		t_dst[i] = t_src[i];
		i++;
	}
	return (t_dst);
}
