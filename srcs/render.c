/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:53:36 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 15:02:50 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void		render_realtime(t_minirt *rt)
{
	barrier_wait(&rt->ready);
	barrier_wait(&rt->done);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}

void		write_block(unsigned int *img, unsigned int color, int i, int j,int dx, int dy, int sizex)
{
	int a;
	int b;

	a = -1;
	while (++a < dy)
	{
		b = -1;
		while (++b < dy)
		{
			img[(j * dy + a) * sizex +
					i * dx + b] = color;
		}
	}
}

void		t_camera_render_lowres(t_minirt *rt, t_camera *c,
									int start, int end)
{
	int		i;
	int		j;
	int		dx;
	int		dy;
	t_vec3	r;

	dx = rt->sizex / rt->resx;
	dy = rt->sizey / rt->resy;
	j = start - 1;
	while (++j < end)
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
			write_block(rt->img->imgdata, ray_trace(rt->world, c->pos, r, 3),
						i, j, dx, dy, rt->sizex);
		}
	}
}

void		render_static(t_minirt *rt)
{
	int				i;
	pthread_t		threads[NB_CORES];
	t_threadargs	args[NB_CORES];

	i = -1;
	while (++i < NB_CORES)
	{
		args[i].c = rt->world->currentcamera;
		args[i].img = rt->img->imgdata;
		args[i].rt = rt;
		args[i].w = rt->world;
		args[i].id = i;
		args[i].threadstart = rt->resy * i / NB_CORES;
		args[i].threadend = rt->resy * (i + 1) / NB_CORES;
		pthread_create(&threads[i],
			NULL, t_camera_render, (void*)&args[i]);
	}
	i = -1;
	while (++i < NB_CORES)
		pthread_join(threads[i], NULL);
	i = -1;
	while (++i < NB_CORES)
		pthread_cancel(threads[i]);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
}

void		*thread_realtime(void *arg)
{
	t_threadargs	*args;
	t_minirt		*rt;

	args = (t_threadargs*)arg;
	rt = (t_minirt*)args->rt;
	while (1)
	{
		barrier_wait(&rt->ready);
		t_camera_render_lowres(rt, rt->world->currentcamera,
								args->threadstart, args->threadend);
		barrier_wait(&rt->done);
	}
	return (0);
}