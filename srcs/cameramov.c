/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameramov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:39:56 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 14:40:21 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <camera.h>

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