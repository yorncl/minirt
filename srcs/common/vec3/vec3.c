/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:09:47 by marvin            #+#    #+#             */
/*   Updated: 2020/01/13 14:46:58 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

t_vec3	v3new(double x, double y, double z)
{
	t_vec3 v;

	v.x = x;
	v.y = y;
	v.z = z;
	return (v);
}

t_vec3	v3cpy(t_vec3 v)
{
	return (v);
}

double	v3magnitude(t_vec3 v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vec3	v3normalize(t_vec3 v)
{
	double m;

	m = v3magnitude(v);
	return (v3new(
		v.x / m,
		v.y / m,
		v.z / m));
}

t_vec3	v3minus(t_vec3 v)
{
	return (v3new(
		-v.x,
		-v.y,
		-v.z));
}
