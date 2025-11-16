/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: monabati <monabati@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 12:00:26 by monabati          #+#    #+#             */
/*   Updated: 2025/06/11 13:17:40 by monabati         ###   ########.fr       */
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

static long long	get_value(const char *str, int *is_overflowed)
{
	int			i;
	long long	result;
	long long	overflow;

	i = 0;
	if (ft_strcmp(str, "-9223372036854775808") == 0)
		return (LONG_MIN);
	result = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		overflow = result;
		result *= 10;
		result += str[i++] - 48;
		if (result / 10 != overflow)
			*is_overflowed = -1;
	}
	return (result);
}

t_exit_stat	ft_atoll(const char *str)
{
	t_exit_stat	stat;
	int			i;
	int			sign;

	i = ft_isspace1(str);
	sign = 1;
	stat.overflow = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign = -1;
	}
	if (sign == -1)
		stat.value = get_value(str + (i - 1), &stat.overflow);
	else
		stat.value = get_value(str + i, &stat.overflow);
	stat.value *= sign;
	return (stat);
}
