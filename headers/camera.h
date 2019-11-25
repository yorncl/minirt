/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:41:52 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 20:41:52 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <vec3.h>

typedef struct 	s_camera
{
	vec3	pos;
	vec3	px;
	vec3	py;
	vec3	pz;
}				camera;

camera	*camera_create();
void	camera_init_pos(camera *c, double x, double y, double z);
void	camera_init_vectors(camera *c, double hfov, double vfov);
void	camera_rot(camera *c, double x, double y, double z);

#endif 
