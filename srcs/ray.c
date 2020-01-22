/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:59:37 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/22 18:36:06 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>

unsigned int	ray_shade(t_obj3d *obj, t_world *w, t_vec3 p, t_vec3 r)
{
	t_obj3d	*ptr;
	t_vec3	v;
	t_color c;
	t_list	*l;
	t_light	*light;

	l = w->lights;
	c.v = 0;
	while (l)
	{
		light = (t_light*)l->content;
		v = v3sub(p, light->pos);
		if (ray_intersect(w, light->pos, v, &ptr) > 0.999)
		{

			t_vec3 new;
			if (v3dot(obj->normal(obj, p, r, v), v) * v3dot(obj->normal(obj, p, r, v), r) >= 0)
				new = obj->normal(obj, p, r, v);
			else
				new = v3minus(obj->normal(obj, p, r, v));
			if (v3dot(new, v) < 0 && v3dot(v3minus(new), v) > 0)
				v.x = v3dot(new, v3normalize(v3minus(v)));
			else
				v.x = 0;
			if (v.x > 0)
				c = lightadd(c,
					dir_l(light, p, obj->material->albedo, v.x), obj);
		}
		l = l->next;
	}
	c = lightadd(c, colormultiplyf(colormultiplyv3(w->ambient->color,
					obj->material->albedo), w->ambient->intensity), obj);
	return (c.v);
}

t_color			dir_l(t_light *l, t_vec3 p,
										t_vec3 albedo, double ratio)
{
	double	r;
	double	coeff;

	r = v3magnitude(v3sub(l->pos, p));
	coeff = l->intensity * ratio / (4 * M_PI * r * r);
	return (colormultiplyf(colormultiplyv3(l->color, albedo),
										coeff > 1 ? 1 : coeff));
}

double			ray_intersect(t_world *w, t_vec3 p, t_vec3 r, t_obj3d **cobj)
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
				*cobj = ptr;
			}
		}
		ptr = ptr->next;
	}
	return (closest);
}

unsigned int	ray_trace(t_world *w, t_vec3 origin,
								t_vec3 r, unsigned int depth)
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
				colormultiplyf((t_color)
					ray_shade(closestobj, w, p, r),
								closestobj->material->diffuse),
				colormultiplyf((t_color)
					ray_trace(w, p, closestobj->normal(closestobj, p),
						depth - 1),
								closestobj->material->specular)).v);
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
	if (obj->type == CYLINDER)
		return (hit_cylinder((t_cylinder*)obj->obj, r, p));
	return (0);
}
