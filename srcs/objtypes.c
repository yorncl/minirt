/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtypes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:01:01 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/12 17:33:58 by mclaudel         ###   ########.fr       */
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
	ptr->obj = s;
	ptr->normal = &sphere_normal;
	
	
	ptr->material = create_material(color, 1, 0);
	
	
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
	ptr->obj = p;
	ptr->normal = &plane_normal;


	ptr->material = create_material(color, 1, 0);
	
	
	return (SUCCESS);
}

int				add_square(t_world *w, vec3 pos, vec3 rot, double side,unsigned int color)
{
	obj3d		*ptr;
	t_square	*p;
	vec3		normal;
	vec3		i;
	vec3		j;

	p = malloc(sizeof(t_square));
	if (p == NULL)
		return (ERROR);
	ptr = obj3dadd(&(w->obj), SQUARE);
	if (ptr == NULL)
	{
		free(p);
		return (ERROR);
	}
	p->pos = pos;
	normal = v3new(0, 0, 1);
	i = v3new(side/2, 0, 0);
	j = v3new(0, side/2, 0);
	v3rotate3(&normal, rot.x, rot.y, rot.z);
	p->p1 = v3add(pos, v3add(j, v3scale(i, -1)));
	p->p2 = v3add(pos, v3add(j, i));
	p->p3 = v3add(pos, v3add(v3scale(j, -1), i));
	p->p4 = v3add(pos, v3add(v3scale(j, -1), v3scale(i, -1)));
	printf("p1 %lf %lf %lf\n", p->p1.x,	p->p1.y, p->p1.z);
	printf("p2 %lf %lf %lf\n", p->p2.x,	p->p2.y, p->p2.z);
	printf("p3 %lf %lf %lf\n", p->p3.x,	p->p3.y, p->p3.z);
	printf("p4 %lf %lf %lf\n", p->p4.x,	p->p4.y, p->p4.z);
	p->n = normal;
	ptr->obj = p;
	ptr->normal = &square_normal;


	ptr->material = create_material(color, 1, 0);
	return (SUCCESS);
}

int				add_triangle(t_world *w, vec3 p1, vec3 p2, vec3 p3,unsigned int color)
{
	obj3d		*ptr;
	t_triangle	*p;
	vec3		normal;

	p = malloc(sizeof(t_triangle));
	if (p == NULL)
		return (ERROR);
	ptr = obj3dadd(&(w->obj), TRIANGLE);
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
