/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:11:32 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/30 15:56:10 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <world.h>

t_world			*world_init(void)
{
	t_world *w;

	w = malloc(sizeof(t_world));
	if (w == NULL)
		return (NULL);
	w->obj = NULL;
	w->light = NULL;
	w->c = NULL;
	return (w);
}

int				add_camera(t_world *w, vec3 pos, vec3 rot, vec3 fov)
{
	camera	*c;

	c = camera_create();
	if (c == NULL)
		return (ERROR);
	camera_init_pos(c, pos.x, pos.y, pos.z);
	camera_init_vectors(c, fov.x, fov.y);
	camera_rot(c, rot.x, rot.y, rot.z);
	w->c = c;
	return (SUCCESS);
}

int				add_ligth(t_world *w, vec3 pos, unsigned int color)
{
	t_light *ptr;

	ptr = ft_calloc(1, sizeof(t_light));
	if (ptr == NULL)
		return (ERROR);
	ptr->color = color;
	ptr->pos = pos;
	w->light = ptr;
	return (SUCCESS);
}
