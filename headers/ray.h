/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:56:51 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 23:56:51 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include <vec3.h>
# include <world.h>
# include <camera.h>

int		ray_trace(camera *c, t_world *w, vec3 r);
int		hit(obj3d *obj, vec3 r, vec3 p);
int		hit_sphere(obj3d *obj, vec3 r, vec3 p);
#endif