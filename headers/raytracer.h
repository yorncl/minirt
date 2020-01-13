/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:22 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/13 16:52:35 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_H
# define RAYTRACER_H

#include <mlx.h>

#include <stdio.h>

#include <parser.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>
#include <camera.h>
#include <raytracerstruct.h>
#include <world.h>
#include <ray.h>


void	t_camera_render(t_camera *c, unsigned int *img, t_world *w, t_minirt *rt);
int		change_camera(int keycode, t_minirt *raytracer);
int		quit_window(t_minirt *rt, int code);
int		key_events(int keycode, t_minirt *raytracer);
void	t_camera_render(t_camera *c, unsigned int *img, t_world *w, t_minirt *rt);
void	free_everything(t_minirt *rt);
#endif