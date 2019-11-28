/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:59:37 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/28 20:05:47 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>

#include <stdio.h>


unsigned int		ray_shade(obj3d *obj, t_light *l, vec3 p, vec3 r)
{
	vec3 n;
	(void) l;
	(void) r;
	n = obj->normal(obj, p);
	return (
		(unsigned int)(0xff * ((n.x + 1) * 0.5)) * 256 * 256 +
		(unsigned int)(0xff * ((n.y + 1) * 0.5)) * 256 +
		(unsigned int)(0xff * ((n.z + 1) * 0.5))
	);
}

unsigned int	ray_trace(camera *c, t_world *w, vec3 r)
{
	double 	closest;
	double 	t;
	vec3	p;
	obj3d	*ptr;
	obj3d	*closestobj;

	ptr = w->obj;
	closest = -1;
	while (ptr)
	{
		if ((t = hit(ptr, r, c->pos)) != NOHIT)
		{
			if (closest == -1 || (t < closest && t > 0))
			{
				closest = t;
				closestobj = ptr;
			}
		}
		ptr = ptr->next;
	}
	if (closest != -1)
	{
		p = v3add(c->pos, v3scale(r, closest));
		unsigned int a = ray_shade(closestobj, w->light, p, r);
		return (a);
	}
	pixel pix;
	pix.v = 0;
	// Gradient
	// p.color.r = (unsigned int)( (1 - (r.z + 1)/2) * 0xff);
	// p.color.g = (unsigned int)( (1 - (r.z + 1)/2) * 0xff + ((r.z + 1)/4) * 0xff);
	// p.color.b = (unsigned int)( (1 - (r.z + 1)/2) * 0xff + ((r.z + 1)/2) * 0xff);
	return (pix.v);
}

double			hit(obj3d *obj, vec3 r, vec3 p)
{
	if (obj->type == SPHERE)
		return (hit_sphere((t_sphere *)obj->obj, r, p));
	return (0);
}

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
	return (delta > 0 ? (-b - sqrt(delta)) / (2.0 * a) : -1);
}
