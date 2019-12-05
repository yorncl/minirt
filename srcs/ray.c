/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:59:37 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/05 15:27:17 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>

#include <stdio.h>


unsigned int		ray_shade(obj3d *obj, t_world *w, vec3 p, vec3 r, unsigned int depth)
{
	obj3d *ptr;
	vec3 n;
	vec3 v;
	double i;
	double ratio;

	(void) r;
	// if (obj->color == 0x00123456)
	// {
	// 	return (ray_trace(w, p, obj->normal(obj, p)));
	// }
	v = v3sub(p, w->light->pos);
	i = ray_intersect(w, w->light->pos, v, &ptr);
	if (i > 0.95)
	{
		n = obj->normal(obj, p);
		ratio = fabs(v3dot(n, v3normalize(v3minus(v))));
		if (ratio > 0)
		{
			unsigned int ptn = (unsigned int)
				(left_color(w->light->color, obj->material->albedo, ratio) * obj->material->diffuse);
			return ((unsigned int)(ptn * obj->material->diffuse) + 
					(unsigned int)(ray_trace(w, p, n, depth - 1) * obj->material->specular * 0.04));
		}
	}
	return (0xff000000);
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
		if ((t = hit(ptr, r, p)) > 0)
		{
			if (closest == -1 || (t < closest))
			{
				closest = t;
				*closestobj = ptr;
			}
		}
		ptr = ptr->next;
	}
	// printf("%lf %lf %lf\n", r.x, r.y, r.z);
	return (closest);
}

unsigned int	ray_trace(t_world *w, vec3 origin, vec3 r, unsigned int depth)
{
	double 	closest;
	vec3	p;
	obj3d	*closestobj;

	if (depth == 0)
		return (0);
	closest = ray_intersect(w, origin, r, &closestobj);
	if (closest != -1)
	{
		p = v3add(origin, v3scale(r, closest));
		// printf("%lf %lf %lf\n", p.x, p.y, p.z);
		return (ray_shade(closestobj, w, p, r, depth));
	}
	// pixel pix;
	// pix.v = 0;
	// Gradient
	// p.color.r = (unsigned int)( (1 - (r.z + 1)/2) * 0xff);
	// p.color.g = (unsigned int)( (1 - (r.z + 1)/2) * 0xff + ((r.z + 1)/4) * 0xff);
	// p.color.b = (unsigned int)( (1 - (r.z + 1)/2) * 0xff + ((r.z + 1)/2) * 0xff);
	// return (pix.v);
	return (0);
}

double			hit(obj3d *obj, vec3 r, vec3 p)
{
	if (obj->type == SPHERE)
		return (hit_sphere((t_sphere *)obj->obj, r, p));
	if (obj->type == PLANE)
		return (hit_plane((t_plane *)obj->obj, r, p));
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
