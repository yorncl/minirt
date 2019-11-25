/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addsub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:18:39 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 19:18:39 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

vec3	v3add(vec3 a, vec3 b)
{
	return v3new(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
}

vec3	v3add3(vec3 a, double x, double y, double z)
{
	return v3new(
		a.x + x,
		a.y + y,
		a.z + z
	);
}

vec3	v3sub(vec3 a, vec3 b)
{
	return v3new(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	);
}

vec3	v3sub3(vec3 a, double x, double y, double z)
{
	return v3new(
		a.x - x,
		a.y - y,
		a.z - z
	);
}