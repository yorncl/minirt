/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 13:26:55 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/29 13:35:54 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void		render_static(t_minirt *rt)
{
	t_threadargs	args;

	args.c = rt->world->currentcamera;
	args.img = rt->img->imgdata;
	args.rt = rt;
	args.w = rt->world;
	args.threadstart = 0;
	args.threadend = rt->resy;
	t_camera_render(&args);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}
