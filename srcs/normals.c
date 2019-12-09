/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:48:01 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/09 11:23:52 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objs.h>

#include <stdio.h>

vec3	sphere_normal(obj3d *obj, vec3 p, vec3 o)
{
	t_sphere	*ptr;
	vec3		v;
	double		m;

	(void)o;
	ptr = (t_sphere*)(obj->obj);
	v = v3sub(p, ptr->pos);
	m = v3magnitude(v);
	return (v3new(v.x / m, v.y / m, v.z / m));
}

vec3	plane_normal(obj3d *obj, vec3 p, vec3 o)
{
	t_plane *ptr;

	(void)p;
	(void)o;
	ptr = (t_plane*)(obj->obj);
	return (ptr->n);
}

vec3	square_normal(obj3d *obj, vec3 p, vec3 o)
{
	t_square *ptr;

	(void)p;
	(void)o;
	ptr = (t_square*)(obj->obj);
	return (ptr->n);
}
