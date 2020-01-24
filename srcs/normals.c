/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:48:01 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/24 04:51:10 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objs.h>

t_vec3	sphere_normal(t_obj3d *obj, t_vec3 p, t_vec3 o)
{
	t_sphere	*ptr;
	t_vec3		v;
	double		m;

	(void)o;
	ptr = (t_sphere*)(obj->obj);
	v = v3sub(p, ptr->pos);
	m = v3magnitude(v);
	return (v3new(v.x / m, v.y / m, v.z / m));
}

t_vec3	plane_normal(t_obj3d *obj, t_vec3 p, t_vec3 o)
{
	t_plane *ptr;

	(void)p;
	(void)o;
	ptr = (t_plane*)(obj->obj);
	return (ptr->n);
}

t_vec3	square_normal(t_obj3d *obj, t_vec3 p, t_vec3 o)
{
	t_square *ptr;

	(void)p;
	(void)o;
	ptr = (t_square*)(obj->obj);
	return (ptr->n);
}

t_vec3	triangle_normal(t_obj3d *obj, t_vec3 p, t_vec3 o)
{
	t_square *ptr;

	(void)p;
	(void)o;
	ptr = (t_square*)(obj->obj);
	return (ptr->n);
}

t_vec3	cylinder_normal(t_obj3d *obj, t_vec3 p, t_vec3 o)
{
	t_vec3		v;
	t_cylinder	*ptr;

	(void)o;
	ptr = (t_cylinder*)obj->obj;
	v = v3sub(p, ptr->pos);
	v = v3cross(v, ptr->dir);
	return (v3normalize(v3cross(v, ptr->dir)));
}
