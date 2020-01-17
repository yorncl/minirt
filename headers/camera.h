/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 20:41:52 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/17 18:12:30 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAMERA_H
# define CAMERA_H

# include <vec3.h>
# include <libft.h>

# define MVCAMSPEED	0.4
# define RTCAMSPEED	0.01

# define FORWARD	1
# define BACKWARD	2
# define LEFT		4
# define RIGHT		8
# define RFORWARD	16
# define RBACKWARD	32
# define RLEFT		64
# define RRIGHT		128
# define RROLL		256
# define LROLL		512

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
void			t_camera_rot_itself(t_camera *c, double x, double y, double z);
t_camera		*get_camera(t_list *cam, int i);
#endif
