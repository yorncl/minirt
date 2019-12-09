/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:27:41 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/09 17:02:03 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

#include <macro.h>
#include <camera.h>
#include <libft.h>
#include <light.h>
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
int				add_ligth(t_world *w, vec3 pos, double intensity, unsigned int color);

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
int				add_plane(t_world *w, vec3 pos, vec3 rot, unsigned int color);
int				add_square(t_world *w, vec3 pos, vec3 rot, double side,unsigned int color); 
#endif
