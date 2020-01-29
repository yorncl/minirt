/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:37:27 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 14:38:07 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

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
