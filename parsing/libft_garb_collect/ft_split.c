/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 10:00:13 by monabati          #+#    #+#             */
/*   Updated: 2025/05/24 22:01:28 by monabati         ###   ########.fr       */
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
		{
			flag = 1;
		}
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

static char	**str_free(char **str, size_t i)
{
	size_t	k;

	k = 0;
	while (k < i)
	{
		free(str[k++]);
	}
	free(str);
	return (NULL);
}

static char	**fill_words(char **str, char const *s, char c, size_t words)
{
	size_t	i;
	size_t	j;
	size_t	x;
	int		word_len;

	i = 0;
	x = 0;
	while (i < words)
	{
		j = 0;
		word_len = count_aword(&s[x], c);
		str[i] = (char *)malloc(sizeof(char) * (word_len + 1));
		if (!str[i])
			return (str_free(str, i));
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

//normal ft_split() func.
char	**ft_split(char const *s, char c)
{
	char	**str;
	size_t	words;

	if (!s)
		return (NULL);
	words = count_words(s, c);
	str = (char **) malloc(sizeof(char *) * (words + 1));
	if (!str)
		return (NULL);
	str = fill_words(str, s, c, words);
	return (str);
}
