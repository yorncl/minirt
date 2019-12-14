/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addsub.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:18:39 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/14 14:36:38 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

t_vec3	v3add(t_vec3 a, t_vec3 b)
{
	return v3new(
		a.x + b.x,
		a.y + b.y,
		a.z + b.z
	);
}

t_vec3	v3add3(t_vec3 a, double x, double y, double z)
{
	return v3new(
		a.x + x,
		a.y + y,
		a.z + z
	);
}

t_vec3	v3sub(t_vec3 a, t_vec3 b)
{
	return v3new(
		a.x - b.x,
		a.y - b.y,
		a.z - b.z
	);
}

t_vec3	v3sub3(t_vec3 a, double x, double y, double z)
{
	return v3new(
		a.x - x,
		a.y - y,
		a.z - z
	);
}