/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 08:57:52 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/09 18:26:18 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>

double			hit_sphere(t_sphere *obj, vec3 r, vec3 p)
{
	vec3	oc;
	double	a;
	double	b;
	double	c;
	double	delta;

	v3set(&oc, p.x - obj->pos.x, p.y - obj->pos.y, p.z - obj->pos.z);
	a = v3dot(r, r);
	b = 2.0 * v3dot(oc, r);
	c = v3dot(oc, oc) - obj->radius * obj->radius;
	delta = b * b - 4 * a * c;
	return (delta > 0 ? (-b - sqrt(delta)) / (2.0 * a) : NOHIT);
}

double			hit_plane(t_plane *obj, vec3 r, vec3 p)
{
	double denom;
	double t;

	denom = v3dot(r, obj->n);
	if (fabs(denom) > 0.000001)
	{
		t = v3dot(v3sub(obj->pos, p), obj->n) / denom;
		return (t > 0 ? t : NOHIT);
	}
	return (NOHIT);
}

double			hit_square(t_square *obj, vec3 r, vec3 p)
{
	double t;

	if ((t = hit_plane((t_plane*)obj, r, p)) != NOHIT)
	{
		return (t);
	}
	return (NOHIT);
}
