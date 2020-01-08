/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:41:52 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/08 16:46:59 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <vec3.h>
# include <libft.h>

typedef struct	s_camera
{
	t_vec3	pos;
	t_vec3	px;
	t_vec3	py;
	t_vec3	pz;
}				t_camera;

t_camera		*t_camera_create();
void			t_camera_init_pos(t_camera *c, double x, double y, double z);
void			t_camera_init_vectors(t_camera *c, double hfov, double vfov);
void			t_camera_rot(t_camera *c, double x, double y, double z);
t_camera		*get_camera(t_list *cam, int i);
#endif
