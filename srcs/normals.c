/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:48:01 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/03 14:16:25 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <objs.h>

#include <stdio.h>

vec3	sphere_normal(obj3d *obj, vec3 p)
{
	t_sphere *ptr;
	vec3 v;
	double m;

	ptr = (t_sphere*)(obj->obj);
	v =	v3sub(p, ptr->pos);
	m = v3magnitude(v);
	return (v3new(v.x / m, v.y / m, v.z / m));
}


vec3	plane_normal(obj3d *obj, vec3 p)
{
	t_plane *ptr;

	(void) p;
	ptr = (t_plane*)(obj->obj);
	return (ptr->n);
}