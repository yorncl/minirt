/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 12:35:32 by mclaudel          #+#    #+#             */
/*   Updated: 2019/10/17 16:57:33 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list *newl;
	t_list *el;

	if (!lst || !f || !del)
		return (0);
	newl = 0;
	while (lst)
	{
		if (!(el = ft_lstnew(f(lst->content))))
		{
			ft_lstclear(&newl, del);
			return (0);
		}
		ft_lstadd_back(&newl, el);
		lst = lst->next;
	}
	return (newl);
}
