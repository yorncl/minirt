/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 16:42:05 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/15 10:25:52 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

int		change_camera(int keycode, t_minirt *rt)
{
	t_world *w;

	w = rt->world;
	if (keycode == KEY_X)
	{
		if (w->camindex + 1 == w->nbcameras)
			w->camindex = 0;
		else
			w->camindex++;
	}
	if (keycode == KEY_Z)
	{
		if (w->camindex == 0)
			w->camindex = w->nbcameras - 1;
		else
			w->camindex--;
	}
	w->currentcamera = get_camera(w->cameras, w->camindex);
	render_static(rt);
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

void	*t_camera_render(void *arg)
{
	int		i;
	int		j;
	t_vec3	r;
	t_threadargs *args;

	args = arg;
	j = args->threadstart - 1;
	while (++j < args->threadend)
	{
		i = -1;
		while (++i < args->rt->resx)
		{
			r.x = args->c->px.x - args->c->py.x - args->c->pz.x +
				(2 * i * args->c->py.x / args->rt->resx) + (2 * j * args->c->pz.x / args->rt->resy);
			r.y = args->c->px.y - args->c->py.y - args->c->pz.y +
				(2 * i * args->c->py.y / args->rt->resx) + (2 * j * args->c->pz.y / args->rt->resy);
			r.z = args->c->px.z - args->c->py.z - args->c->pz.z +
				(2 * i * args->c->py.z / args->rt->resx) + (2 * j * args->c->pz.z / args->rt->resy);
			args->img[j * args->rt->resx + i] = ray_trace(args->w, args->c->pos, r, 3);
		}
	}
	return (0);
}
