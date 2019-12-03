/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:56:51 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/03 14:10:11 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <vec3.h>
# include <world.h>
# include <camera.h>
# include <macro.h>
# include <objs.h>

# define HIT 1
# define NOHIT -1

unsigned int		ray_trace(t_world *w, vec3 origin, vec3 r);
double				ray_intersect(t_world *w, vec3 p, vec3 r, obj3d **closestobj);
unsigned int		ray_shade(obj3d *obj, t_world *w, vec3 p, vec3 r);
double				hit(obj3d *obj, vec3 r, vec3 p);
double				hit_sphere(t_sphere *obj, vec3 r, vec3 p);
double				hit_plane(t_plane *obj, vec3 r, vec3 p);

#endif