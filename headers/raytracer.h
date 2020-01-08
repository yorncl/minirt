/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:22 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/08 17:32:15 by mclaudel         ###   ########.fr       */
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
#include <world.h>
#include <ray.h>

typedef struct	s_image
{
	void			*img;
	unsigned int	*imgdata;
	int				depth;
	int				linesize;
	int				edian;
}				t_image;

typedef struct s_minirt
{
	void	*mlx;
	void	*win;
	t_image *img;
	int		resx;
	int		resy;
	int		frame;
	t_world *world;
}				t_minirt;

void	t_camera_render(t_camera *c, unsigned int *img, t_world *w, t_minirt *rt);
int		change_camera(int keycode, t_minirt *raytracer);
int		quit_window(t_minirt *rt);
int		key_events(int keycode, t_minirt *raytracer);
void	t_camera_render(t_camera *c, unsigned int *img, t_world *w, t_minirt *rt);
#endif