/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:19:28 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/14 15:03:45 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

void	v3rotate(t_vec3 *a, t_vec3 b)
{
	v3rotatex(a, b.x);
	v3rotatey(a, b.y);
	v3rotatez(a, b.z);
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
	v->z = - s * tmp + c * v->z;
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