/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 14:34:39 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/25 16:39:53 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ray.h>

t_color			lightadd(t_color light1, t_color light2, t_obj3d *obj)
{
	t_color			object;
	unsigned int	tmp;

	object.v = 0xFFFFFF;
	object = colormultiplyv3(object, obj->material->albedo);
	tmp = light1.color.r + light2.color.r;
	object.color.r = object.color.r < tmp ? object.color.r : tmp;
	tmp = light1.color.g + light2.color.g;
	object.color.g = object.color.g < tmp ? object.color.g : tmp;
	tmp = light1.color.b + light2.color.b;
	object.color.b = object.color.b < tmp ? object.color.b : tmp;
	return (object);
}
