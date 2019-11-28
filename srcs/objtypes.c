/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objtypes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:01:01 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/28 17:02:55 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

int			add_sphere(t_world *w, vec3 pos, int radius, unsigned int color)
{
	obj3d		*ptr;
	t_sphere	*s;

	s = malloc(sizeof(t_sphere));
	if (s == NULL)
		return (ERROR);
	ptr = obj3dadd(&(w->obj), SPHERE);
	if (ptr == NULL)
	{
		free(s);
		return (ERROR);
	}
	s->radius = radius;
	s->pos = pos;
	ptr->color = color;
	ptr->obj = s;
	ptr->normal = &sphere_normal;
	return (SUCCESS);
}
