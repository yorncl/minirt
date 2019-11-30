/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 16:06:27 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/23 22:17:48 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char		*desti;
	const char	*source;
	char		*enddest;
	const char	*endsource;

	if (dst == src)
		return (dst);
	desti = dst;
	source = src;
	enddest = desti + (len - 1);
	endsource = source + (len - 1);
	if (desti < source)
	{
		while (len--)
			*desti++ = *source++;
	}
	else
	{
		while (len--)
			*enddest-- = *endsource--;
	}
	return (dst);
}
