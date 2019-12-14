/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 21:35:45 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/28 15:37:06 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <camera.h>

t_camera	*t_camera_create()
{
	t_camera *c;

	c = ft_calloc(1, sizeof(t_camera));
	if (c == NULL)
		return (NULL);
	return (c);
}

void	t_camera_init_pos(t_camera *c, double x, double y, double z)
{
	c->pos = v3new(
		x,
		y,
		z
	);
}

void	t_camera_init_vectors(t_camera *c, double hfov, double vfov)
{
	hfov /= 2;
	vfov /= 2;
	c->px = v3new(1,0,0);
	c->py = v3new(0,tan(hfov * (M_PI / 180)),0);
	c->pz = v3new(0,0,-tan(vfov * (M_PI / 180)));
}

void	t_camera_rot(t_camera *c, double x, double y, double z)
{
	v3rotate3(&(c->px), x, y, z);
	v3rotate3(&(c->py), x, y, z);
	v3rotate3(&(c->pz), x, y, z);
}