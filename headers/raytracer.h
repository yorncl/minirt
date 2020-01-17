/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:22 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/17 13:20:29 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

#include <mlx.h>

#include <stdio.h>

#include <stdatomic.h>
#include <parser.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>
#include <limits.h>
#include <camera.h>
#include <raytracerstruct.h>
#include <world.h>
#include <ray.h>


# define KEY_A 		0
# define KEY_W 		13
# define KEY_D 		2
# define KEY_S 		1
# define KEY_LEFT 	123
# define KEY_UP 	126
# define KEY_RIGHT 	124
# define KEY_DOWN	125
# define KEY_Q		12
# define KEY_E		14
# define KEY_R		15
# define KEY_Z		6
# define KEY_X		7
# define KEY_ESCAPE	53



void	render_static(t_minirt *rt);
void	*t_camera_render(void *arg);
int		change_camera(int keycode, t_minirt *raytracer);
int		quit_window(t_minirt *rt, int code);
int		key_events(int keycode, t_minirt *raytracer);
void	free_everything(t_minirt *rt);


int		key_pressed(int keycode, t_minirt *rt);
int		key_released(int keycode, t_minirt *rt);
void	toggle_realtime(t_minirt *rt);

/*
**	multithread
*/
void	t_camera_render_lowres(t_minirt *rt, t_camera *c, int start, int end, unsigned int *img);
void	init_threads(t_minirt *rt);
void	kill_threads(t_minirt *rt);
void 	render_realtime(t_minirt *rt);
void	*thread_realtime(void *arg);

/*
**	mutex
*/

#endif