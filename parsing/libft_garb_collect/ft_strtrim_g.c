/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim_g.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 10:26:32 by monabati          #+#    #+#             */
/*   Updated: 2025/05/24 22:05:26 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*str_start(char const *str, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (str[i])
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == str[i])
				break ;
			j++;
		}
		if (!set[j])
			return ((char *)&str[i]);
		i++;
	}
	return ((char *)&str[i]);
}

static char	*str_end(char const *str, char const *set, size_t len)
{
	size_t	j;

	if (len == 0)
		return ((char *)str);
	len--;
	while (len != (size_t)(-1))
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == str[len])
				break ;
			j++;
		}
		if (!set[j])
			return ((char *)&str[len]);
		len--;
	}
	return ((char *)&str[len]);
}

//ft_strtrim func with garbage collector.
char	*ft_strtrim_g(char const *s1, char const *set, t_garbage **garb_coll)
{
	char	*start;
	char	*end;
	size_t	length;
	char	*str_trim;

	if (!s1 || !set)
		return (NULL);
	if (s1[0] == '\0')
		return (ft_strdup_g("", garb_coll));
	start = str_start(s1, set);
	end = str_end(s1, set, ft_strlen(s1));
	if (start > end)
		return (ft_strdup_g("", garb_coll));
	length = end - start + 1;
	str_trim = (char *) ft_malloc(sizeof(char) * (length + 1), garb_coll);
	if (!str_trim)
		return (NULL);
	ft_memcpy(str_trim, start, length);
	str_trim[length] = '\0';
	return (str_trim);
}
