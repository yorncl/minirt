/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/13 14:30:17 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 14:22:38 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <camera.h>

t_camera	*t_camera_create(void)
{
	t_camera *c;

	c = ft_calloc(1, sizeof(t_camera));
	if (c == NULL)
		return (NULL);
	return (c);
}

void		t_camera_init_pos(t_camera *c, double x, double y, double z)
{
	c->pos = v3new(
		x,
		y,
		z);
}

void		t_camera_init_vectors(t_camera *c, double hfov, double vfov)
{
	hfov /= 2;
	vfov /= 2;
	c->px = v3new(1, 0, 0);
	c->py = v3new(0, tan(hfov * (M_PI / 180)), 0);
	c->pz = v3new(0, 0, -tan(vfov * (M_PI / 180)));
}

void		t_camera_rot(t_camera *c, double x, double y, double z)
{
	v3rotate3(&(c->px), x, y, z);
	v3rotate3(&(c->py), x, y, z);
	v3rotate3(&(c->pz), x, y, z);
}

void		t_camera_rot_itself(t_camera *c, double x, double y, double z)
{
	v3rotateaxis(&c->py, c->px, x);
	v3rotateaxis(&c->pz, c->px, x);
	v3rotateaxis(&c->px, c->py, y);
	v3rotateaxis(&c->pz, c->py, y);
	v3rotateaxis(&c->px, c->pz, z);
	v3rotateaxis(&c->py, c->pz, z);
}

t_camera	*get_camera(t_list *cam, int i)
{
	t_camera	*c;

	c = (t_camera*)cam->content;
	while (i--)
	{
		cam = cam->next;
		c = (t_camera*)cam->content;
	}
	return (c);
}
