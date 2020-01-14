/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:42:05 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/13 17:12:57 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

int		change_camera(int keycode, t_minirt *raytracer)
{
	t_world *w;

	w = raytracer->world;
	if (keycode == 124)
	{
		if (w->camindex + 1 == w->nbcameras)
			w->camindex = 0;
		else
			w->camindex++;
	}
	if (keycode == 123)
	{
		if (w->camindex == 0)
			w->camindex = w->nbcameras - 1;
		else
			w->camindex--;
	}
	w->currentcamera = get_camera(w->cameras, w->camindex);
	t_camera_render(w->currentcamera,
		raytracer->img->imgdata, raytracer->world, raytracer);
	mlx_put_image_to_window(raytracer->mlx, raytracer->win,
		raytracer->img->img, 0, 0);
	return (0);
}

int		quit_window(t_minirt *rt, int code)
{
	free_everything(rt);
	write(1, "Exiting\n", 8);
	system("MallocStackLoggingNoCompact=1 leaks run_tests");
	exit(code);
	return (code);
}

void	t_camera_render(t_camera *c, unsigned int *img,
							t_world *w, t_minirt *rt)
{
	int		i;
	int		j;
	t_vec3	r;

	j = -1;
	while (++j < rt->resy)
	{
		i = -1;
		while (++i < rt->resx)
		{
			r.x = c->px.x - c->py.x - c->pz.x +
				(2 * i * c->py.x / rt->resx) + (2 * j * c->pz.x / rt->resy);
			r.y = c->px.y - c->py.y - c->pz.y +
				(2 * i * c->py.y / rt->resx) + (2 * j * c->pz.y / rt->resy);
			r.z = c->px.z - c->py.z - c->pz.z +
				(2 * i * c->py.z / rt->resx) + (2 * j * c->pz.z / rt->resy);
			img[j * rt->resx + i] = ray_trace(w, c->pos, r, 3);
		}
	}
}
