/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:27:41 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/08 16:51:14 by mclaudel         ###   ########.fr       */
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
	int			nbcameras;
	int			camindex;
}				t_world;

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
int				add_sphere(t_world *w, t_vec3 pos, double radius, unsigned int color);
int				add_plane(t_world *w, t_vec3 pos, t_vec3 rot, unsigned int color);
int				add_square(t_world *w, t_vec3 pos, t_vec3 rot, double side,unsigned int color); 
int				add_triangle(t_world *w, t_vec3 p1, t_vec3 p2, t_vec3 p3,unsigned int color);
int				add_cylinder(t_world *w, t_vec3 pos, t_vec3 rot, double height, double radius, unsigned int color);
#endif
