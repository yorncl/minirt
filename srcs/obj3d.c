/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:12:05 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/25 10:12:05 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

obj3d			*obj3dnew(obj_type type)
{
	obj3d *o;

	o = malloc(sizeof(obj3d));
	if (o == NULL)
		return (NULL);
	o->type = type;
	o->next = NULL;
	return (o);
}

obj3d			*obj3dlast(obj3d *ptr)
{
	if (!ptr)
		return (0);
	while (ptr->next)
		ptr = ptr->next;
	return (ptr);
}

obj3d			*obj3dadd(obj3d **ptr, obj_type type)
{
	obj3d	*o;

	if (!ptr)
		return (0);
	o = obj3dlast(*ptr);
	if(o == NULL)
	{
		*ptr = obj3dnew(type);
		return (*ptr);
	}
	o->next = obj3dnew(type);
	return (o->next);
}
