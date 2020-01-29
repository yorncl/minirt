/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 10:11:32 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/08 15:49:08 by mclaudel         ###   ########.fr       */
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
	w->lights = NULL;
	w->ambient = NULL;
	w->cameras = NULL;
	return (w);
}

int				add_t_camera(t_world *w, t_vec3 pos, t_vec3 rot, t_vec3 fov)
{
	t_camera	*c;
	t_list		*el;

	c = t_camera_create();
	if (c == NULL)
		return (ERROR);
	t_camera_init_pos(c, pos.x, pos.y, pos.z);
	t_camera_init_vectors(c, fov.x, fov.y);
	t_camera_rot(c, rot.x, rot.y, rot.z);
	el = ft_lstnew(c);
	if (el == NULL)
	{
		free(c);
		return (ERROR);
	}
	ft_lstadd_front(&w->cameras, el);
	return (SUCCESS);
}

int				add_ligth(t_world *w, t_vec3 pos,
	double intensity, unsigned int color)
{
	t_light *ptr;
	t_list	*a;

	ptr = ft_calloc(1, sizeof(t_light));
	if (ptr == NULL)
		return (ERROR);
	ptr->color.v = color;
	ptr->pos = pos;
	ptr->intensity = intensity;
	a = ft_lstnew(ptr);
	if (a == NULL)
	{
		free(ptr);
		return (ERROR);
	}
	ft_lstadd_front(&(w->lights), a);
	return (SUCCESS);
}

int				add_ambient(t_world *w, double intensity, unsigned int color)
{
	t_light *ptr;

	ptr = ft_calloc(1, sizeof(t_light));
	if (ptr == NULL)
		return (ERROR);
	ptr->intensity = intensity;
	ptr->color = (t_color)color;
	w->ambient = ptr;
	return (SUCCESS);
}
