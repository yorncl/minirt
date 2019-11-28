/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:48:01 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/28 18:51:40 by mclaudel         ###   ########.fr       */
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
