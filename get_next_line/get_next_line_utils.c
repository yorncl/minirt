/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:58:25 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/29 16:52:05 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substrg(char const *s, unsigned int start, size_t len)
{
	char	*dest;
	size_t	i;

	if (!(dest = (malloc(len + 1))))
		return (0);
	dest[len] = 0;
	i = 0;
	while (i < len)
	{
		dest[i] = s[start + i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int		endofline(char *str, int len)
{
	int i;

	if (!str)
		return (-1);
	i = -1;
	while (++i < len)
		if (str[i] == '\n')
			return (i);
	return (-1);
}

t_listg	*ft_lstnewg(int fd)
{
	t_listg *el;

	if (!(el = malloc(sizeof(t_listg))))
		return (NULL);
	el->fd = fd;
	el->charsleft = 0;
	el->size = 0;
	el->next = 0;
	return (el);
}

t_listg	*ft_lst_by_fd(int fd, t_listg **listg)
{
	t_listg *prev;
	t_listg *l;

	if (!*listg)
	{
		*listg = ft_lstnewg(fd);
		return (*listg);
	}
	l = *listg;
	while (l)
		if (fd == l->fd)
			return (l);
		else
		{
			prev = l;
			l = l->next;
		}
	prev->next = ft_lstnewg(fd);
	return (prev->next);
}

void	ft_lst_remove(int fd, t_listg **listg)
{
	t_listg *prev;
	t_listg *curr;

	curr = *listg;
	if (curr->fd == fd)
	{
		curr = curr->next;
		free(*listg);
		*listg = curr;
		return ;
	}
	prev = curr;
	curr = curr->next;
	while (curr)
	{
		if (curr->fd == fd)
		{
			prev->next = curr->next;
			free(curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}
