/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 11:05:16 by monabati          #+#    #+#             */
/*   Updated: 2025/06/17 16:32:52 by monabati         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_isspace1(const char *str)
{
	int	i;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f'
		|| str[i] == '\r' || str[i] == ' ')
		i++;
	return (i);
}

static int	ft_cheker(int c)
{
	if (c < 0)
		return (0);
	return (-1);
}

int	ft_atoi(const char *str)
{
	int		i;
	long	result;
	long	overflow;
	int		sign;

	if (!str)
		return (0);
	i = ft_isspace1(str);
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	result = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		overflow = result;
		result *= 10;
		result += str[i++] - 48;
		if (result / 10 != overflow)
			return (ft_cheker(sign));
	}
	return (result * sign);
}
