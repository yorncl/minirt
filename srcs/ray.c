/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:59:37 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 23:59:37 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>

#include <stdio.h>
typedef union  pixel
{
	unsigned int v;
	struct {
		unsigned int b : 8;
		unsigned int g : 8; 
		unsigned int r : 8;
		unsigned int a : 8;
	}	color;
}				pixel;

unsigned int	ray_trace(camera *c, t_world *w, vec3 r)
{
	double closest;
	double tmp;
	obj3d *ptr;
	obj3d *closestobj;

	ptr = w->obj;
	closest = -1;
	while (ptr)
	{
		if ((tmp = hit(ptr, r, c->pos)) != NOHIT)
		{
			if (closest == -1 ||( tmp < closest && tmp > 0))
				{
					closest = tmp;
					closestobj = ptr;
				}
		}
		ptr = ptr->next;
	}
	if (closest != -1)
		return (closestobj->color);
	pixel p;
	p.v = 0;
	p.color.r = (unsigned int)( (1 - (r.z + 1)/2) * 0xff);
	p.color.g = (unsigned int)( (1 - (r.z + 1)/2) * 0xff + ((r.z + 1)/4) * 0xff);
	p.color.b = (unsigned int)( (1 - (r.z + 1)/2) * 0xff + ((r.z + 1)/2) * 0xff);
	return (p.v);
}

double			hit(obj3d *obj, vec3 r, vec3 p)
{
	if (obj->type == SPHERE)
		return (hit_sphere((t_sphere *)obj->obj, r, p));
	return (0);
}

double			hit_sphere(t_sphere *obj, vec3 r, vec3 p)
{
	vec3 oc;
	double a;
	double b;
	double c;
	double delta;

	v3set(&oc, p.x - obj->pos.x,p.y - obj->pos.y, p.z - obj->pos.z);
	a = v3dot(r, r);
	b = 2.0 * v3dot(oc, r);
	c = v3dot(oc, oc) - obj->radius*obj->radius;
	delta = b*b - 4*a*c;
	return (delta > 0 ? (-b - sqrt(delta) ) / (2.0*a) : -1);
}
