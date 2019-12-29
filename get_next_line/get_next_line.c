/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 10:58:05 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/31 17:42:55 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_memjoin(char const *s1, int l1, char const *s2, int l2)
{
	char	*str;
	char	*ptr;

	if (!(str = malloc(l1 + l2 + 1)))
		return (0);
	ptr = str;
	if (l1)
		while (l1--)
			*ptr++ = *s1++;
	if (l2)
		while (l2--)
			*ptr++ = *s2++;
	*ptr = '\0';
	return (str);
}

int		managecharsleft(t_list *l, t_line *s_line)
{
	char	*tmp;
	int		e;

	if (l->charsleft == 0)
		return (0);
	if ((e = endofline(l->charsleft, l->size)) != -1)
	{
		if (!(*(s_line->line) = ft_substr(l->charsleft, 0, e)))
			return (-1);
		tmp = l->charsleft;
		if (l->size == e + 1)
			l->charsleft = 0;
		else if (!(l->charsleft = ft_substr(l->charsleft, e + 1, l->size - e)))
			return (-1);
		free(tmp);
		l->size -= e + 1;
		return (1);
	}
	else
	{
		*(s_line->line) = l->charsleft;
		l->charsleft = 0;
		s_line->size = l->size;
		return (l->size = 0);
	}
}

int		allocandconcat(t_line *s_line, char *buff, int tocpy)
{
	char *tmp;

	tmp = *(s_line->line);
	if (!(*(s_line->line) =
		ft_memjoin(*(s_line->line), s_line->size, buff, tocpy)))
		return (-1);
	s_line->size += tocpy;
	free(tmp);
	return (0);
}

int		readloop(int fd, char *buff, t_line *s_line, t_list *current)
{
	int rd;
	int eol;
	int i;

	while ((rd = read(fd, buff, BUFFER_SIZE)) > 0 &&
		(eol = endofline(buff, rd)) == -1)
	{
		if (allocandconcat(s_line, buff, rd))
			return (-1);
		i = -1;
		while (++i < BUFFER_SIZE)
			buff[i] = 0;
	}
	if (rd == -1)
		return (-1);
	if (rd == 0)
		return (0);
	if (allocandconcat(s_line, buff, eol))
		return (-1);
	if (eol + 1 == rd)
		current->charsleft = 0;
	else if (!(current->charsleft = ft_substr(buff, eol + 1, rd - eol - 1)))
		return (-1);
	current->size = rd - eol - 1;
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*list;
	t_list			*current;
	t_line			s_line;
	char			*buff;
	int				i;

	if (BUFFER_SIZE < 0 ||
		!line || fd < 0 || !(current = ft_lst_by_fd(fd, &list)))
		return (-1);
	*line = 0;
	s_line = (t_line) {.size = 0, .line = line};
	if ((i = managecharsleft(current, &s_line)) == 1)
		return (1);
	if (i == -1 || !(buff = malloc(sizeof(char) * BUFFER_SIZE)))
		return (-1);
	if ((i = readloop(fd, buff, &s_line, current)) == 0 && !*line)
	{
		if (!(*line = malloc(1)))
			return (-1);
		*line[0] = '\0';
	}
	if (i == 0)
		ft_lst_remove(fd, &list);
	free(buff);
	return (i);
}
