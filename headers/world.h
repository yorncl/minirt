/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:27:41 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 23:27:41 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WORLD_H
# define WORLD_H

#include <vec3.h>
#include <macro.h>
#include <camera.h>
#include <stdlib.h>

typedef enum 	obj_type{
	SPHERE,
	PLANE
}				obj_type;

typedef struct	s_sphere
{
	vec3			pos;
	int				radius;
}				t_sphere;

typedef struct	obj3d
{
	obj_type		type;
	unsigned int	color;
	void			*obj;
	struct obj3d	*next;
}				obj3d;

typedef struct 	s_world
{
	camera	*c;
	obj3d	*obj;
}				t_world;

/*
**	world.c
*/
t_world			*world_init();
int				add_camera(t_world *w, vec3 pos, vec3 rot, vec3 fov);
/*
**	obj3d.c
*/
obj3d			*obj3dnew(obj_type type);
obj3d			*obj3dlast(obj3d *ptr);
obj3d			*obj3dadd(obj3d **ptr, obj_type type);
/*
**	objtypes.c
*/
int				add_sphere(t_world *w, vec3 pos, int radius, unsigned int color);

#endif
