/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:57:28 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/31 15:53:41 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 31
# endif

# include <stdlib.h>
# include <unistd.h>

typedef struct	s_list
{
	int				fd;
	char			*charsleft;
	int				size;
	struct s_list	*next;
}				t_list;

typedef struct	s_line
{
	char	**line;
	int		size;
}				t_line;

/*
**	get_next_line.c
*/
int				get_next_line(int fd, char **line);
int				managecharsleft(t_list *l, t_line *s_line);
int				allocandconcat(t_line *s_line, char *buff, int tocpy);
char			*ft_memjoin(char const *s1, int l1, char const *s2, int l2);
int				readloop(int fd, char *buff, t_line *s_line, t_list *current);

/*
**	get_next_line_utils.c
*/
int				endofline(char *str, int len);
void			ft_lst_remove(int fd, t_list **list);
char			*ft_substr(char const *s, unsigned int start, size_t len);
t_list			*ft_lstnew(int fd);
t_list			*ft_lst_by_fd(int fd, t_list **list);

#endif
