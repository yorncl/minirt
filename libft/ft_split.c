/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 12:28:17 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/19 12:54:41 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int		nbstring(const char *s, char c)
{
	int		nb;
	char	*ptr;

	nb = 0;
	ptr = (char*)s;
	while (*ptr)
	{
		while (*ptr && *ptr == c)
			ptr++;
		if (*ptr != '\0')
			nb++;
		while (*ptr && *ptr != c)
			ptr++;
	}
	return (nb);
}

static	void	*freebuffs(char **buff)
{
	char **tmp;

	tmp = buff;
	while (*tmp)
		free(*tmp++);
	free(buff);
	return (0);
}

char			**ft_split(char const *s, char c)
{
	char	*ptr;
	char	*last;
	char	**strs;
	char	**k;

	if (!s || !(strs = ft_calloc(nbstring(s, c) + 1, sizeof(char*))))
		return (0);
	ptr = (char*)s;
	k = strs;
	while (*ptr)
	{
		while (*ptr && *ptr == c)
			ptr++;
		last = ptr;
		while (*ptr && *ptr != c)
			ptr++;
		if (*last && !(*k = ft_calloc(1, (ptr - last + 1) * sizeof(char))))
			return (freebuffs(strs));
		ft_memcpy(*k, last, ptr - last);
		k++;
	}
	return (strs);
}
