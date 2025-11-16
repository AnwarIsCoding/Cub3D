/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_g.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:00:13 by monabati          #+#    #+#             */
/*   Updated: 2025/05/28 14:53:30 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	words;
	int		flag;

	words = 0;
	flag = 0;
	while (*s)
	{
		if (*s == c)
		{
			if (flag)
			{
				words++;
				flag = 0;
			}
		}
		else
			flag = 1;
		s++;
	}
	if (flag)
		words++;
	return (words);
}

static int	count_aword(char const *s, char c)
{
	int	count;

	count = 0;
	while (*s == c)
		s++;
	while (*s && *s != c)
	{
		s++;
		count++;
	}
	return (count);
}

static char	**fill_words(char **str, char const *s,
	char c, t_garbage **garb_coll)
{
	size_t	i;
	size_t	j;
	size_t	x;
	int		word_len;

	i = 0;
	x = 0;
	while (i < count_words(s, c))
	{
		j = 0;
		word_len = count_aword(&s[x], c);
		str[i] = (char *) ft_malloc(sizeof(char) * (word_len + 1), garb_coll);
		if (!str[i])
			return (NULL);
		while (s[x] == c)
			x++;
		while ((s[x] != c) && s[x])
			str[i][j++] = s[x++];
		str[i][j] = '\0';
		i++;
	}
	str[i] = NULL;
	return (str);
}

//ft_split() func with garbage collector.
char	**ft_split_g(char const *s, char c, t_garbage **garb_coll)
{
	char	**str;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	str = (char **) ft_malloc(sizeof(char *) * (words + 1), garb_coll);
	if (!str)
		return (NULL);
	str = fill_words(str, s, c, garb_coll);
	return (str);
}
