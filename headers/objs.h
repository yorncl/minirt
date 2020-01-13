/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objs.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/28 16:51:38 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/13 16:09:20 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OBJS_H
# define OBJS_H

# include <vec3.h>
# include <color.h>
# include <material.h>

typedef enum	e_obj_type
{
	SPHERE,
	PLANE,
	SQUARE,
	TRIANGLE,
	CYLINDER
}				t_obj_type;

typedef struct	s_sphere
{
	t_vec3			pos;
	double			radius;
}				t_sphere;

typedef struct	s_plane
{
	t_vec3			pos;
	t_vec3			n;
	t_vec3			(*normal)();
}				t_plane;

typedef struct	s_square
{
	t_vec3			pos;
	t_vec3			n;
	t_vec3			(*normal)();
	t_vec3			p1;
	t_vec3			p2;
	t_vec3			p3;
	t_vec3			p4;
}				t_square;

typedef struct	s_triangle
{
	t_vec3			pos;
	t_vec3			n;
	t_vec3			(*normal)();
	t_vec3			p1;
	t_vec3			p2;
	t_vec3			p3;
}				t_triangle;

typedef struct	s_cylinder
{
	t_vec3			pos;
	t_vec3			pos2;
	t_vec3			dir;
	double			radius;
	double			height;
	t_vec3			(*normal)();
}				t_cylinder;

typedef struct	s_obj3d
{
	t_obj_type		type;
	t_material		*material;
	void			*obj;
	struct s_obj3d	*next;
	t_vec3			(*normal)();
}				t_obj3d;

/*
**	Normals
*/
t_vec3			sphere_normal(t_obj3d *obj, t_vec3 p, t_vec3 o);
t_vec3			plane_normal(t_obj3d *obj, t_vec3 p, t_vec3 o);
t_vec3			square_normal(t_obj3d *obj, t_vec3 p, t_vec3 o);
t_vec3			triangle_normal(t_obj3d *obj, t_vec3 p, t_vec3 o);
t_vec3			cylinder_normal(t_obj3d *obj, t_vec3 p, t_vec3 o);
#endif
