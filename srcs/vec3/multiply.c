/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiply.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:20:26 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 19:20:26 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

void	v3scale(vec3 *v, double s)
{
	v->x *= s;
	v->y *= s;
	v->z *= s;
}

vec3	*v3cross(vec3 *a, vec3 *b)
{
	return (
		v3new(
			a->y * b->z - a->z * b->y,
			a->z * b->x - a->x * b->z,
			a->x * b->y - a->y * b->x
		)
	);
}

double	v3dot(vec3 *a, vec3 *b)
{
	return (a->x * b->x +
			a->y * b->y +
			a->z * b->z);
}
