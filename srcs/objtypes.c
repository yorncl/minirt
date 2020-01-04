/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtypes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:01:01 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/16 15:40:03 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

#include <stdio.h>

int			add_sphere(t_world *w, t_vec3 pos, double radius, unsigned int color)
{
	t_obj3d		*ptr;
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (s == NULL)
		return (ERROR);
	ptr = t_obj3dadd(&(w->obj), SPHERE);
	if (ptr == NULL)
	{
		free(s);
		return (ERROR);
	}
	s->radius = radius;
	s->pos = pos;
	ptr->obj = s;
	ptr->normal = &sphere_normal;
	
	
	ptr->material = create_material(color, 1, 0);
	
	
	return (SUCCESS);
}

int				add_plane(t_world *w, t_vec3 pos, t_vec3 rot, unsigned int color)
{
	t_obj3d		*ptr;
	t_plane		*p;
	t_vec3		normal;

	p = malloc(sizeof(t_plane));
	if (p == NULL)
		return (ERROR);
	ptr = t_obj3dadd(&(w->obj), PLANE);
	if (ptr == NULL)
	{
		free(p);
		return (ERROR);
	}
	p->pos = pos;
	normal = v3new(0, 0, 1);
	v3rotate3(&normal, rot.x, rot.y, rot.z);
	p->n = normal;
	ptr->obj = p;
	ptr->normal = &plane_normal;


	ptr->material = create_material(color, 1, 0);
	
	
	return (SUCCESS);
}

int				add_square(t_world *w, t_vec3 pos, t_vec3 rot, double side,unsigned int color)
{
	t_obj3d		*ptr;
	t_square	*p;
	t_vec3		normal;
	t_vec3		i;
	t_vec3		j;

	p = malloc(sizeof(t_square));
	if (p == NULL)
		return (ERROR);
	ptr = t_obj3dadd(&(w->obj), SQUARE);
	if (ptr == NULL)
	{
		free(p);
		return (ERROR);
	}
	p->pos = pos;
	normal = v3new(0, 0, 1);
	i = v3new(side / 2, 0, 0);
	j = v3new(0, side / 2, 0);
	v3rotate3(&normal, rot.x, rot.y, rot.z);
	p->p1 = v3add(pos, v3add(j, v3scale(i, -1)));
	p->p2 = v3add(pos, v3add(j, i));
	p->p3 = v3add(pos, v3add(v3scale(j, -1), i));
	p->p4 = v3add(pos, v3add(v3scale(j, -1), v3scale(i, -1)));
	p->n = normal;
	ptr->obj = p;
	ptr->normal = &square_normal;
	ptr->material = create_material(color, 1, 0);
	return (SUCCESS);
}

int				add_triangle(t_world *w, t_vec3 p1, t_vec3 p2, t_vec3 p3,unsigned int color)
{
	t_obj3d		*ptr;
	t_triangle	*p;
	t_vec3		normal;

	p = malloc(sizeof(t_triangle));
	if (p == NULL)
		return (ERROR);
	ptr = t_obj3dadd(&(w->obj), TRIANGLE);
	if (ptr == NULL)
	{
		free(p);
		return (ERROR);
	}
	p->pos = p1;
	normal = v3normalize(v3cross(v3sub(p1, p2), v3sub(p1, p3)));
	p->p1 = p1;
	p->p2 = p2;
	p->p3 = p3;
	p->n = normal;
	ptr->obj = p;
	ptr->normal = &triangle_normal;


	ptr->material = create_material(color, 1, 0);

	return (SUCCESS);
}

int			add_cylinder(t_world *w, t_vec3 pos, t_vec3 rot, double height, double radius, unsigned int color)
{
	t_obj3d		*ptr;
	t_cylinder	*s;
	t_vec3		dir;

	s = malloc(sizeof(t_cylinder));
	if (s == NULL)
		return (ERROR);
	ptr = t_obj3dadd(&(w->obj), CYLINDER);
	if (ptr == NULL)
	{
		free(s);
		return (ERROR);
	}
	dir = v3new(0,0,1);
	v3rotate(&dir, rot);
	s->radius = radius;
	s->height = height;
	s->pos = pos;
	s->dir = dir;
	ptr->obj = s;
	ptr->normal = &cylinder_normal;
	
	
	ptr->material = create_material(color, 0.9, 0.1);
	
	
	return (SUCCESS);
}
