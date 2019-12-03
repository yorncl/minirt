/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:51:38 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/03 16:59:23 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJS_H
# define OBJS_H

# include <vec3.h>
# include <color.h>
# include <material.h>

typedef enum 	obj_type{
	SPHERE,
	PLANE
}				obj_type;

typedef struct	s_sphere
{
	vec3			pos;
	double			radius;
}				t_sphere;

typedef struct	s_plane
{
	vec3			pos;
	vec3			n;
	vec3			(*normal)();
}				t_plane;

typedef struct	obj3d
{
	obj_type		type;
	t_material		*material;
	void			*obj;
	struct obj3d	*next;
	vec3			(*normal)();
}				obj3d;

typedef struct	s_light
{
	vec3			pos;
	unsigned int	color;
}				t_light;

/*
**	Normals
*/
vec3	sphere_normal(obj3d *obj, vec3 p);
vec3	plane_normal(obj3d *obj, vec3 p);
#endif