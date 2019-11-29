/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:59:37 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/29 16:15:46 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>

#include <stdio.h>


unsigned int		ray_shade(obj3d *obj, t_world *w, vec3 p)
{
	obj3d *ptr;
	vec3 n;
	vec3 v;
	double i;
	double ratio;

	n = obj->normal(obj, p);
	v = v3sub(w->light->pos, p);
	i = ray_intersect(w, w->light->pos, v, &ptr);
	(void) ptr;
	// printf("%lf\n", i);

	ratio = v3dot(n, v3normalize(v));
	
	if(ratio > 0)
		return (
			// ((unsigned int)(0xffffff * ratio)) - (sub)
			viewed_color((t_color)obj->color, (t_color)w->light->color, ratio)
		);
	else
		return (0);
	// return (
	// 	(unsigned int)(0xff * ((n.x + 1) * 0.5)) * 256 * 256 +
	// 	(unsigned int)(0xff * ((n.y + 1) * 0.5)) * 256 +
	// 	(unsigned int)(0xff * ((n.z + 1) * 0.5))
	// );
}

double			ray_intersect(t_world *w, vec3 p, vec3 r, obj3d **closestobj)
{
	obj3d	*ptr;
	double 	closest;
	double 	t;

	ptr = w->obj;
	closest = -1;
	while (ptr)
	{
		if ((t = hit(ptr, r, p)) != NOHIT)
		{
			if (closest == -1 || (t < closest && t > 0))
			{
				closest = t;
				*closestobj = ptr;
			}
		}
		ptr = ptr->next;
	}
	return (closest);
}

unsigned int	ray_trace(camera *c, t_world *w, vec3 r)
{
	double 	closest;
	vec3	p;
	obj3d	*closestobj;

	closest = ray_intersect(w, c->pos, r, &closestobj);
	if (closest != -1)
	{
		p = v3add(c->pos, v3scale(r, closest));
		return (ray_shade(closestobj, w, p));
	}
	// pixel pix;
	// pix.v = 0;
	// Gradient
	// p.color.r = (unsigned int)( (1 - (r.z + 1)/2) * 0xff);
	// p.color.g = (unsigned int)( (1 - (r.z + 1)/2) * 0xff + ((r.z + 1)/4) * 0xff);
	// p.color.b = (unsigned int)( (1 - (r.z + 1)/2) * 0xff + ((r.z + 1)/2) * 0xff);
	// return (pix.v);
	return (0x0);
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
