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

int		ray_trace(camera *c, t_world *w, vec3 *r)
{
	double closest;
	double tmp;
	obj3d *ptr;
	obj3d *closestobj;

	ptr = w->obj;
	closest = -1;
	while (ptr)
	{
		if (hit(ptr, r, c->pos))
		{
			tmp = ptr->pos->x * ptr->pos->x + ptr->pos->y * ptr->pos->y + ptr->pos->z * ptr->pos->z;
			if (closest == -1 || tmp < closest)
				{
					closest = tmp;
					closestobj = ptr;
				}
		}
		ptr = ptr->next;
	}
	if(closest != -1)
		return (closestobj->color);
	return (r->z > 0 ? 50000000 :  0);
}

int		hit(obj3d *obj, vec3 *r, vec3 *p)
{
	if (obj->type == SPHERE)
		return (hit_sphere(obj, r, p));
	return (0);
}

int		hit_sphere(obj3d *obj, vec3 *r, vec3 *p)
{
	vec3 oc;
	double a;
	double b;
	double c;

	v3set(&oc, p->x - obj->pos->x,p->y - obj->pos->y, p->z - obj->pos->z);
	a = v3dot(r, r);
	b = 2.0 * v3dot(&oc, r);
	c = v3dot(&oc, &oc) - obj->w*obj->w;
	return (b*b - 4*a*c > 0);
}
