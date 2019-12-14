/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_obj3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:12:05 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/25 10:12:05 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

t_obj3d			*t_obj3dnew(t_obj_type type)
{
	t_obj3d *o;

	o = malloc(sizeof(t_obj3d));
	if (o == NULL)
		return (NULL);
	o->type = type;
	o->next = NULL;
	return (o);
}

t_obj3d			*t_obj3dlast(t_obj3d *ptr)
{
	if (!ptr)
		return (0);
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

t_obj3d			*t_obj3dadd(t_obj3d **ptr, t_obj_type type)
{
	t_obj3d	*o;

	if (!ptr)
		return (0);
	o = t_obj3dlast(*ptr);
	if(o == NULL)
	{
		*ptr = t_obj3dnew(type);
		return (*ptr);
	}
	o->next = t_obj3dnew(type);
	return (o->next);
}
