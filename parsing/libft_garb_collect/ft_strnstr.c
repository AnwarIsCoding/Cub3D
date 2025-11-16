/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 13:35:01 by monabati          #+#    #+#             */
/*   Updated: 2024/11/09 16:04:28 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_search(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	j;
	char	*tmp_haystack;
	char	*tmp_needle;

	tmp_haystack = (char *) haystack;
	tmp_needle = (char *) needle;
	i = 0;
	while (tmp_haystack[i] && i < len)
	{
		j = 0;
		if (tmp_haystack[i] == tmp_needle[j])
		{
			while (tmp_needle[j] && (tmp_needle[j] == tmp_haystack[i + j])
				&& (i + j < len))
				j++;
			if (tmp_needle[j] == '\0')
				return (&tmp_haystack[i]);
		}
		i++;
	}
	return (NULL);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	char	*tmp_haystack;
	char	*tmp_needle;

	tmp_haystack = (char *) haystack;
	tmp_needle = (char *) needle;
	if (tmp_needle[0] == '\0')
		return (tmp_haystack);
	if (len == 0)
		return (NULL);
	return (ft_search(haystack, needle, len));
}
