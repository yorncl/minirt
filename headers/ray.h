/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:56:51 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/28 17:17:11 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

# include <vec3.h>
# include <world.h>
# include <camera.h>
# include <macro.h>
# include <objs.h>
typedef union  pixel
{
	unsigned int v;
	struct {
		unsigned int b : 8;
		unsigned int g : 8; 
		unsigned int r : 8;
		unsigned int a : 8;
	}	color;
}				pixel;

# define HIT 1
# define NOHIT -1

unsigned int		ray_trace(camera *c, t_world *w, vec3 r);
unsigned int		ray_shade(obj3d *obj, t_light *l, vec3 p, vec3 r);
double				hit(obj3d *obj, vec3 r, vec3 p);
double				hit_sphere(t_sphere *obj, vec3 r, vec3 p);
#endif