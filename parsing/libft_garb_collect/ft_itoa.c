/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 11:49:45 by monabati          #+#    #+#             */
/*   Updated: 2025/05/24 23:26:10 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_num(int n)
{
	int	count;

	count = 0;
	if (n == 0)
		count++;
	if (n < 0)
	{
		count++;
		n *= -1;
	}
	while (n != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}

//normal ft_itoa() func.
char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*result;

	i = count_num(n);
	nb = n;
	result = (char *) malloc(sizeof(char) * ((int)i + 1));
	if (!result)
		return (NULL);
	if (nb == 0)
		result[0] = '0';
	if (nb < 0)
	{
		result[0] = '-';
		nb *= -1;
	}
	result[i--] = '\0';
	while (nb != 0)
	{
		result[i] = ((nb % 10) + 48);
		nb = nb / 10;
		i--;
	}
	return (result);
}
