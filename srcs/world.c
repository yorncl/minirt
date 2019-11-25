/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:11:32 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/25 10:11:32 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

t_world			*world_init()
{
	t_world *w;

	w = malloc(sizeof(t_world));
	if (w == NULL)
		return (NULL);
	w->obj = NULL;
	w->c = NULL;
	return (w);
}

int				add_camera(t_world *w, vec3 pos, vec3 rot, vec3 fov)
{
	camera	*c;

	c = camera_create();
	if (c == NULL)
		return (ERROR);
	camera_init_pos(c,pos.x,pos.y,pos.z);
	camera_init_vectors(c, fov.x,fov.y);
	camera_rot(c, rot.x, rot.y, rot.z);
	w->c = c;
	return (SUCCESS);
}
