/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtypes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:01:01 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 14:36:41 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

int				add_sphere(t_world *w, t_objargs args, double radius)
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
	s->pos = args.pos;
	ptr->obj = s;
	ptr->normal = &sphere_normal;
	ptr->material = create_material(args.color, 1, 0);
	return (SUCCESS);
}

int				add_plane(t_world *w, t_objargs args)
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
	p->pos = args.pos;
	normal = v3new(0, 0, 1);
	v3rotate3(&normal, args.rot.x, args.rot.y, args.rot.z);
	p->n = normal;
	ptr->obj = p;
	ptr->normal = &plane_normal;
	ptr->material = create_material(args.color, 1, 0);
	return (SUCCESS);
}

int				add_square(t_world *w, t_objargs args, double side)
{
	t_obj3d		*ptr;
	t_square	*p;
	t_vec3		i;
	t_vec3		j;

	if ((p = malloc(sizeof(t_square))) == NULL)
		return (ERROR);
	if ((ptr = t_obj3dadd(&(w->obj), SQUARE)) == NULL)
	{
		free(p);
		return (ERROR);
	}
	p->pos = args.pos;
	p->n = v3new(0, 0, 1);
	i = v3new(side / 2, 0, 0);
	j = v3new(0, side / 2, 0);
	v3rotate3(&p->n, args.rot.x, args.rot.y, args.rot.z);
	p->p1 = v3add(args.pos, v3add(j, v3scale(i, -1)));
	p->p2 = v3add(args.pos, v3add(j, i));
	p->p3 = v3add(args.pos, v3add(v3scale(j, -1), i));
	p->p4 = v3add(args.pos, v3add(v3scale(j, -1), v3scale(i, -1)));
	ptr->obj = p;
	ptr->normal = &square_normal;
	ptr->material = create_material(args.color, 1, 0);
	return (SUCCESS);
}

int				add_triangle(t_world *w, t_objargs args, t_vec3 p2, t_vec3 p3)
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
	p->pos = args.pos;
	normal = v3normalize(v3cross(v3sub(args.pos, p2), v3sub(args.pos, p3)));
	p->p1 = args.pos;
	p->p2 = p2;
	p->p3 = p3;
	p->n = normal;
	ptr->obj = p;
	ptr->normal = &triangle_normal;
	ptr->material = create_material(args.color, 1, 0);
	return (SUCCESS);
}

int				add_cylinder(t_world *w, t_objargs args,
					double height, double radius)
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
	dir = v3new(0, 0, 1);
	v3rotate(&dir, args.rot);
	s->radius = radius;
	s->height = height;
	s->pos = args.pos;
	s->pos2 = v3add(args.pos, v3scale(dir, height));
	s->dir = dir;
	ptr->obj = s;
	ptr->normal = &cylinder_normal;
	ptr->material = create_material(args.color, 0.9, 0.1);
	return (SUCCESS);
}
