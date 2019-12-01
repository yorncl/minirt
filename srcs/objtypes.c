/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtypes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:01:01 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/29 14:03:00 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

#include <stdio.h>

int			add_sphere(t_world *w, vec3 pos, double radius, unsigned int color)
{
	obj3d		*ptr;
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (s == NULL)
		return (ERROR);
	ptr = obj3dadd(&(w->obj), SPHERE);
	if (ptr == NULL)
	{
		free(s);
		return (ERROR);
	}
	s->radius = radius;
	s->pos = pos;
	ptr->color = color;
	ptr->obj = s;
	ptr->normal = &sphere_normal;
	return (SUCCESS);
}

int				add_plane(t_world *w, vec3 pos, vec3 rot, unsigned int color)
{
	obj3d		*ptr;
	t_plane		*p;
	vec3		normal;

	p = malloc(sizeof(t_plane));
	if (p == NULL)
		return (ERROR);
	ptr = obj3dadd(&(w->obj), PLANE);
	if (ptr == NULL)
	{
		free(p);
		return (ERROR);
	}
	p->pos = pos;
	normal = v3new(0, 0, 1);
	v3rotate3(&normal, rot.x, rot.y, rot.z);
	p->n = normal;
	ptr->color = color;
	ptr->obj = p;
	ptr->normal = &plane_normal;
	return (SUCCESS);
}
