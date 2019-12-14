/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:59:37 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/14 14:36:38 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>

#include <stdio.h>


unsigned int		ray_shade(t_obj3d *obj, t_world *w, t_vec3 p, t_vec3 r, unsigned int depth)
{
	t_obj3d *ptr;
	t_vec3 n;
	t_vec3 v;
	double ratio;

	t_color color;
	(void) r;
	(void) depth;

	t_list *l;
	t_light *light;

	l = w->lights;
	color.v = 0;
	while (l)
	{
		light = (t_light*)l->content;
		v = v3sub(p, light->pos);
		if (obj->type == PLANE || obj->type == SQUARE || obj->type == TRIANGLE)
			if (!isfacinglight(obj, v, r))
			{
				l = l->next;
				continue;
			}
		ratio = ray_intersect(w, light->pos, v, &ptr);
		if (ratio > 0.99)
		{
			n = obj->normal(obj, p, r, v);
			ratio = fabs(v3dot(n, v3normalize(v)));
			if (ratio > 0)
				color = coloradd(color, direct_lightning(light, p, obj->material->albedo, ratio));
		}
		l = l->next;
	}

	// color += light_diffuse(,) + light_specular() + light_(refracted);

	return (color.v);
}

t_color				direct_lightning(t_light *l, t_vec3 p, t_vec3 albedo, double ratio)
{
	double	r;
	double	coeff;

	r = v3magnitude(v3sub(l->pos, p));
	coeff = l->intensity * ratio / (4 * M_PI * r * r);
	return (colormultiplyf(colormultiplyv3(l->color, albedo), coeff));
}

int isfacinglight(t_obj3d *obj, t_vec3 l, t_vec3 r)
{
	return (v3dot(obj->normal(obj), l) * v3dot(obj->normal(obj), r) > 0);
}

double			ray_intersect(t_world *w, t_vec3 p, t_vec3 r, t_obj3d **closestobj)
{
	t_obj3d	*ptr;
	double	closest;
	double	t;

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

unsigned int	ray_trace(t_world *w, t_vec3 origin, t_vec3 r, unsigned int depth)
{
	double	closest;
	t_vec3	p;
	t_obj3d	*closestobj;

	if (depth == 0)
		return (0);
	closest = ray_intersect(w, origin, r, &closestobj);
	if (closest != -1)
	{
		p = v3add(origin, v3scale(r, closest));
		return (
			coloradd(
				colormultiplyf((t_color)ray_shade(closestobj, w, p, r, depth), closestobj->material->diffuse),
				colormultiplyf((t_color)ray_trace(w, p, closestobj->normal(closestobj, p), depth - 1), closestobj->material->specular)
			).v
		);
	}
	return (0);
}

double			hit(t_obj3d *obj, t_vec3 r, t_vec3 p)
{
	if (obj->type == SPHERE)
		return (hit_sphere((t_sphere*)obj->obj, r, p));
	if (obj->type == PLANE)
		return (hit_plane((t_plane*)obj->obj, r, p));
	if (obj->type == SQUARE)
		return (hit_square((t_square*)obj->obj, r, p));
	if (obj->type == TRIANGLE)
		return (hit_triangle((t_triangle*)obj->obj, r, p));
	return (0);
}
