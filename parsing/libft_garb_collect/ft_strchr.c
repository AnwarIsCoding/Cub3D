/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:36:32 by monabati          #+#    #+#             */
/*   Updated: 2024/11/07 11:41:53 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	tmp;
	size_t	i;

	i = 0;
	tmp = (char) c;
	while (s[i])
	{
		if (s[i] == tmp)
			return ((char *) &s[i]);
		i++;
	}
	if (s[i] == tmp)
		return ((char *) &s[i]);
	return (NULL);
}
