/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:27:41 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/28 19:33:53 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

#include <macro.h>
#include <camera.h>
#include <libft.h>
#include <objs.h>

typedef struct 	s_world
{
	camera	*c;
	obj3d	*obj;
	t_light	*light;
}				t_world;

/*
**	world.c
*/
t_world			*world_init(void);
int				add_camera(t_world *w, vec3 pos, vec3 rot, vec3 fov);
int				add_ligth(t_world *w, vec3 pos, unsigned int color);

/*
**	obj3d.c
*/
obj3d			*obj3dnew(obj_type type);
obj3d			*obj3dlast(obj3d *ptr);
obj3d			*obj3dadd(obj3d **ptr, obj_type type);
/*
**	objtypes.c
*/
int				add_sphere(t_world *w, vec3 pos, double radius, unsigned int color);

#endif
