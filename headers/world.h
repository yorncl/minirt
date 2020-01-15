/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:27:41 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/10 14:23:02 by mclaudel         ###   ########.fr       */
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
	t_obj3d		*obj;
	t_list		*lights;
	t_list		*cameras;
	t_light		*ambient;
	t_camera	*currentcamera;
	int			nbcameras;
	int			camindex;
}				t_world;

/*
**	Arguments for norm
*/
typedef struct 	s_objargs
{
	t_vec3			pos;
	t_vec3			rot;
	unsigned int	color;
}				t_objargs;

/*
**	world.c
*/
t_world			*world_init(void);
int				add_t_camera(t_world *w, t_vec3 pos, t_vec3 rot, t_vec3 fov);
int				add_ligth(t_world *w, t_vec3 pos, double intensity, unsigned int color);
int				add_ambient(t_world *w, double intensity, unsigned int color);
/*
**	t_obj3d.c
*/
t_obj3d			*t_obj3dnew(t_obj_type type);
t_obj3d			*t_obj3dlast(t_obj3d *ptr);
t_obj3d			*t_obj3dadd(t_obj3d **ptr, t_obj_type type);
/*
**	objtypes.c
*/
int				add_sphere(t_world *w, t_objargs args, double radius);
int				add_plane(t_world *w, t_objargs args);
int				add_square(t_world *w, t_objargs args, double side); 
int				add_triangle(t_world *w, t_objargs args, t_vec3 p2, t_vec3 p3);
int				add_cylinder(t_world *w, t_objargs args, double height, double radius);
#endif
