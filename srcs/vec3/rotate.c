/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:19:28 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/13 14:46:35 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

void	v3rotate(t_vec3 *a, t_vec3 b)
{
	v3rotatex(a, b.x);
	v3rotatey(a, b.y);
	v3rotatez(a, b.z);
}

void	v3rotateaxis(t_vec3 *a, t_vec3 u, double ro)
{
	t_vec3 v;
	double cosro;
	double sinro;

	cosro = cos(ro);
	sinro = sin(ro);
	u = v3normalize(u);
	v = v3new(
		a->x,
		a->y,
		a->z);
	a->x = 
		(cosro + u.x * u.x * (1 - cosro)) * v.x +
		(u.x * u.y * (1 - cosro) - u.z * sinro) * v.y +
		(u.x * u.z * (1 - cosro) + u.y * sinro) * v.z;
	a->y = 
		(u.x * u.y * (1 - cosro) + u.z * sinro) * v.x +
		(cosro + u.y * u.y * (1 - cosro)) * v.y +
		(u.y * u.z * (1 - cosro) - u.x * sinro) * v.z;
	a->z = 
		(u.x * u.z * (1 - cosro) - u.y * sinro) * v.x +
		(u.y * u.z * (1 - cosro) + u.x * sinro) * v.y +
		(cosro + u.z * u.z * (1 - cosro)) * v.z;
}

void	v3rotate3(t_vec3 *v, double ox, double oy, double oz)
{
	v3rotatex(v, ox);
	v3rotatey(v, oy);
	v3rotatez(v, oz);
}

void	v3rotatex(t_vec3 *v, double o)
{
	double tmp;
	double c;
	double s;

	c = cos(o);
	s = sin(o);
	tmp = v->y;
	v->y = c * v->y - s * v->z;
	v->z = s * tmp + c * v->z;
}

void	v3rotatey(t_vec3 *v, double o)
{
	double tmp;
	double c;
	double s;

	c = cos(o);
	s = sin(o);
	tmp = v->x;
	v->x = c * v->x + s * v->z;
	v->z = -s * tmp + c * v->z;
}

void	v3rotatez(t_vec3 *v, double o)
{
	double tmp;
	double c;
	double s;

	c = cos(o);
	s = sin(o);
	tmp = v->x;
	v->x = c * v->x - s * v->y;
	v->y = s * tmp + c * v->y;
}
