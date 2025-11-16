/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:07:14 by monabati          #+#    #+#             */
/*   Updated: 2025/05/04 13:19:15 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*tsrc;
	unsigned char	*tdst;

	tsrc = (unsigned char *) src;
	tdst = (unsigned char *) dst;
	if (tdst > tsrc)
	{
		while (len > 0)
		{
			len--;
			tdst[len] = tsrc[len];
		}
	}
	else if (tdst < tsrc)
	{
		ft_memcpy(dst, src, len);
	}
	return (tdst);
}
