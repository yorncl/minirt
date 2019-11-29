/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:09:47 by marvin            #+#    #+#             */
/*   Updated: 2019/11/29 11:45:28 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

vec3	v3new(double x, double y, double z)
{
	vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

vec3	v3cpy(vec3 v)
{
	return (v);
}

void	v3set(vec3 *v, double x, double y, double z)
{
	v->x = x;
	v->y = y;
	v->z = z;
}

double	v3magnitude(vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

vec3	v3normalize(vec3 v)
{
	double m;

	m = v3magnitude(v);
	return (v3new(
		v.x / m,
		v.y / m,
		v.z / m));
}
