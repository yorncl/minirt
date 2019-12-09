/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:59:37 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/09 23:59:45 by mclaudel         ###   ########.fr       */
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

	t_color color = 0;
	(void) r;
	(void) depth;

	while ()
	v = v3sub(p, w->light->pos);
	i = ray_intersect(w, w->light->pos, v, &ptr);
	if (i > 0.95)
	{
		n = obj->normal(obj, p, r, v);
		ratio = fabs(v3dot(n, v3normalize(v)));
		if (ratio > 0)
			color = coloradd(color,direct_lightning(w->light, p, obj->material->albedo, ratio));
	}
	// color += light_diffuse(,) + light_specular() + light_(refracted);
	return (color.v);
}

t_color				direct_lightning(t_light *l, vec3 p, vec3 albedo, double ratio)
{
	double	r;
	double	coeff;

	r = v3magnitude(v3sub(l->pos, p));
	coeff = l->intensity * ratio / (4 * M_PI * r * r);
	return (colormultiplyf(colormultiplyv3(l->color, albedo), coeff).v);
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
		return (ray_shade(closestobj, w, p, r, depth));
	}
	return (0);
}

double			hit(obj3d *obj, vec3 r, vec3 p)
{
	if (obj->type == SPHERE)
		return (hit_sphere((t_sphere*)obj->obj, r, p));
	if (obj->type == PLANE)
		return (hit_plane((t_plane*)obj->obj, r, p));
	if (obj->type == SQUARE)
		return (hit_square((t_square*)obj->obj, r, p));
	return (0);
}
