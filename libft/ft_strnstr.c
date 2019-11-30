/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:08:43 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/22 15:15:54 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	l;

	i = 0;
	l = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	if (haystack == NULL && len == 0)
		return (0);
	while (*haystack != '\0' && l < len)
	{
		if (*haystack == needle[i])
		{
			while (haystack[i] == needle[i] && haystack[i] && i + l < len)
				i++;
			if (needle[i] == '\0')
				return ((char *)haystack);
			else
				i = 0;
		}
		haystack++;
		l++;
	}
	return (0);
}
