/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:58:25 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/30 08:24:50 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
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

t_list	*ft_lstnew(int fd)
{
	t_list *el;

	if (!(el = malloc(sizeof(t_list))))
		return (NULL);
	el->fd = fd;
	el->charsleft = 0;
	el->size = 0;
	el->next = 0;
	return (el);
}

t_list	*ft_lst_by_fd(int fd, t_list **list)
{
	t_list *prev;
	t_list *l;

	if (!*list)
	{
		*list = ft_lstnew(fd);
		return (*list);
	}
	l = *list;
	while (l)
		if (fd == l->fd)
			return (l);
		else
		{
			prev = l;
			l = l->next;
		}
	prev->next = ft_lstnew(fd);
	return (prev->next);
}

void	ft_lst_remove(int fd, t_list **list)
{
	t_list *prev;
	t_list *curr;

	curr = *list;
	if (curr->fd == fd)
	{
		curr = curr->next;
		free(*list);
		*list = curr;
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
