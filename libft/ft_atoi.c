/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:21:20 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/18 17:23:40 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int value;
	int isneg;

	value = 0;
	isneg = 0;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\v'
		|| *str == '\f' || *str == '\r')
		str++;
	if (*str == '-' || *str == '+')
	{
		isneg = (*str == '-' ? 1 : 0);
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		value *= 10;
		value += 48 - *str;
		str++;
	}
	return (isneg ? value : -value);
}
