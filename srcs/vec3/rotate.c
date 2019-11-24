/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:19:28 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 19:19:28 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

void	v3rotate(vec3 *a, vec3 *b);

void	v3rotate3(vec3 *v, double ox, double oy, double oz)
{
	v3rotateX(v, ox);
	v3rotateY(v, oy);
	v3rotateZ(v, oz);
}

void	v3rotateX(vec3 *v, double o)
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

void	v3rotateY(vec3 *v, double o)
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

void	v3rotateZ(vec3 *v, double o)
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