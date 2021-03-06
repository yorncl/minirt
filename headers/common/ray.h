/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:56:51 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/22 14:35:03 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <vec3.h>
# include <world.h>
# include <camera.h>
# include <macro.h>
# include <objs.h>
# include <light.h>

# define HIT 1
# define NOHIT -1

/*
**	Ray
*/
unsigned int		ray_trace(t_world *w, t_vec3 origin,
												t_vec3 r, unsigned int depth);
double				ray_intersect(t_world *w, t_vec3 p,
												t_vec3 r, t_obj3d **closestobj);
unsigned int		ray_shade(t_obj3d *obj, t_world *w, t_vec3 p, t_vec3 r);
double				hit(t_obj3d *obj, t_vec3 r, t_vec3 p);
t_color				lightadd(t_color light1, t_color light2, t_obj3d *obj);

/*
**	Collisions
*/
double				hit_sphere(t_sphere *obj, t_vec3 r, t_vec3 p);
double				hit_plane(t_plane *obj, t_vec3 r, t_vec3 p);
double				hit_square(t_square *obj, t_vec3 r, t_vec3 p);
double				hit_triangle(t_triangle *obj, t_vec3 r, t_vec3 p);
double				hit_cylinder(t_cylinder *obj, t_vec3 r, t_vec3 p);
#endif
