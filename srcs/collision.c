/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   collision.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 08:57:52 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/14 14:36:38 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>

double			hit_sphere(t_sphere *obj, t_vec3 r, t_vec3 p)
{
	t_vec3	oc;
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

double			hit_plane(t_plane *obj, t_vec3 r, t_vec3 p)
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

double			hit_square(t_square *obj, t_vec3 r, t_vec3 p)
{
	double	t;
	t_vec3	inter;
	int		hitted;

	if ((t = hit_plane((t_plane*)obj, r, p)) != NOHIT)
	{
		hitted = 0;
		inter = v3add(p, v3scale(r, t));
		hitted += v3dot(
			v3cross(v3sub(obj->p1, inter), v3sub(obj->p2, inter)), obj->n) > 0;
		hitted += v3dot(
			v3cross(v3sub(obj->p2, inter), v3sub(obj->p3, inter)), obj->n) > 0;
		hitted += v3dot(
			v3cross(v3sub(obj->p3, inter), v3sub(obj->p4, inter)), obj->n) > 0;
		hitted += v3dot(
			v3cross(v3sub(obj->p4, inter), v3sub(obj->p1, inter)), obj->n) > 0;
		if (hitted == 4 || hitted == 0)
			return (t);
	}
	return (NOHIT);
}

double			hit_triangle(t_triangle *obj, t_vec3 r, t_vec3 p)
{
	double	t;
	t_vec3	inter;
	int		hitted;

	if ((t = hit_plane((t_plane*)obj, r, p)) != NOHIT)
	{
		hitted = 0;
		inter = v3add(p, v3scale(r, t));
		hitted += v3dot(
			v3cross(v3sub(obj->p1, inter), v3sub(obj->p2, inter)), obj->n) > 0;
		hitted += v3dot(
			v3cross(v3sub(obj->p2, inter), v3sub(obj->p3, inter)), obj->n) > 0;
		hitted += v3dot(
			v3cross(v3sub(obj->p3, inter), v3sub(obj->p1, inter)), obj->n) > 0;
		if (hitted == 3 || hitted == 0)
			return (t);
	}
	return (NOHIT);
}
