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

int		key_events(int keycode, t_minirt *rt)
{
	if (keycode == 124 || keycode == 123)
		change_camera(keycode, rt);
	if (keycode == 53)
		quit_window(rt, 0);
	//Z
	if (keycode == 122)
		rt->world->currentcamera->pos = v3add(
			rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->px, 0.2));
	//S
	if (keycode == 115)
		rt->world->currentcamera->pos = v3add(
			rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->px, -0.2));
	//Q
	if (keycode == 113)
		rt->world->currentcamera->pos = v3add(
			rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->py, 0.2));
	//D
	if (keycode == 100)
		rt->world->currentcamera->pos = v3add(
			rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->py, -0.2));
	//gauche
	if (keycode == 65361)
		t_camera_rot(rt->world->currentcamera, 0, 0, -0.05);
	//haut
	if (keycode == 65362)
		t_camera_rot(rt->world->currentcamera, 0.05, 0, 0);
	//droite
	if (keycode == 65363)
		t_camera_rot(rt->world->currentcamera, 0, 0, 0.05);
	//bas
	if (keycode == 65364)
		t_camera_rot(rt->world->currentcamera, -0.05, 0, 0);
	if (keycode == 114)
	{
		rt->realtime = !rt->realtime;
		if (!rt->realtime)
		{
			rt->resx = rt->sizex;
			rt->resy = rt->sizey;
			t_camera_render(rt->world->currentcamera, rt->img->imgdata, rt->world, rt);
			mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
		}
	}
	printf("keycode : %d\n", keycode);
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
