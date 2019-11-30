/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 13:37:12 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/23 23:44:46 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t		i;
	size_t		len;
	char		*dest;
	char		*s;

	s = (char *)src;
	dest = dst;
	i = 0;
	while (i++ < dstsize && *dest != '\0')
		dest++;
	len = dest - dst;
	if (dstsize - len == 0)
		return (len + ft_strlen(src));
	i = len;
	while (*s != '\0')
	{
		if (i++ < dstsize - 1)
		{
			*dest = *s;
			dest++;
		}
		s++;
	}
	*dest = '\0';
	return (len + s - src);
}
