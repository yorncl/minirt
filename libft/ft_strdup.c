/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 18:28:10 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/24 00:02:45 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		*ft_memcpy_bis(void *dst, const void *src, size_t n)
{
	unsigned char	*destination;
	unsigned char	*source;

	destination = (unsigned char *)dst;
	source = (unsigned char *)src;
	if (dst == NULL || src == NULL)
		return (NULL);
	if (n == 0 || dst == src)
		return (dst);
	while (n--)
		*destination++ = *source++;
	*destination = '\0';
	return (dst);
}

char			*ft_strdup(const char *s1)
{
	char	*cpy;

	if (!(cpy = malloc(sizeof(char) * (ft_strlen(s1) + 1))))
		return (0);
	return (ft_memcpy_bis(cpy, s1, ft_strlen(s1)));
}
