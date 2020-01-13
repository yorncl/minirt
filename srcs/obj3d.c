/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:31:53 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/13 16:20:03 by mclaudel         ###   ########.fr       */
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
	if (o == NULL)
	{
		*ptr = t_obj3dnew(type);
		return (*ptr);
	}
	o->next = t_obj3dnew(type);
	return (o->next);
}

void			*free_oneobj3d(t_obj3d *obj)
{
	size_t size;

	if (obj->type == SPHERE)
		size = sizeof(t_sphere);
	if (obj->type == PLANE)
		size = sizeof(t_plane);
	if (obj->type == SQUARE)
		size = sizeof(t_square);
	if (obj->type == TRIANGLE)
		size = sizeof(t_triangle);
	if (obj->type == CYLINDER)
		size = sizeof(t_cylinder);
	ft_bzero(obj->material, sizeof(t_material));
	free(obj->material);
	ft_bzero(obj->obj, size);
	free(obj->obj);
	ft_bzero(obj, sizeof(t_obj3d));
	free(obj);
}

void			*free_allobj3d(t_obj3d *obj)
{
	t_obj3d *next;

	while (obj)
	{
		next = obj->next;
		free_oneobj3d(obj);
		obj = next;
	}
}
