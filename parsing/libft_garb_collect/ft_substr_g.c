/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr_g.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:40:35 by monabati          #+#    #+#             */
/*   Updated: 2025/05/28 14:54:01 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

//ft_substr() func with garbage collector.
char	*ft_substr_g(char const *s, unsigned int start, size_t len,
	t_garbage **garb_coll)
{
	char	*str;
	size_t	i;

	if (!s || len == 0)
		return (ft_strdup_g("", garb_coll));
	if (start > ft_strlen(s))
		return (ft_strdup_g("", garb_coll));
	if (len > (ft_strlen(s) - start))
		len = (ft_strlen(s) - start);
	str = (char *) ft_malloc(sizeof (char) * (len + 1), garb_coll);
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[len] = '\0';
	return (str);
}
