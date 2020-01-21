/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 12:06:59 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

int			parse_filename(char *path)
{
	char *extension;

	extension = ft_strrchr(path, '.');
	if (!extension ||
		ft_strncmp(".rt", extension, ft_max(ft_strlen(extension), 3)) != 0)
		return (ERROR);
	return (SUCCESS);
}

void		free_everything(t_minirt *rt)
{
	t_world *w;

	w = rt->world;
	if (w)
	{
		ft_lstclear(&w->lights, free);
		ft_lstclear(&w->cameras, free);
		if (w->ambient)
		{
			ft_bzero(w->ambient, sizeof(t_light));
			free(w->ambient);
		}
		if (w->obj)
			free_allobj3d(w->obj);
		free(w);
	}
	if (rt->mlx)
	{
		if (rt->img->img)
			mlx_destroy_image(rt->mlx, rt->img->img);
		free(rt->img);
		mlx_destroy_window(rt->mlx, rt->win);
	}
}

int	update_acnt(t_minirt *rt)
{
	rt->acnt++;
	//compare and update ?
	if (rt->acnt == NB_CORES)
		return (1);
	return (0);
}

int		barrier_init(t_barrier *b, int num)
{
	if(num == 0)
        return (-1);
    if(pthread_mutex_init(&b->lock, 0) < 0)
        return (-1);
    if(pthread_cond_init(&b->cond, 0) < 0)
	{
		pthread_mutex_init(&b->lock, 0);
        return (-1);
	}
    b->total = 0;
    b->count = 0;
    return (0);
}

int		barrier_destroy(t_barrier *b)
{
	pthread_cond_destroy(&b->cond);
	pthread_mutex_destroy(&b->lock);
    return (0);
}

int		barrier_wait(t_barrier *b)
{

	pthread_mutex_lock(&b->lock);
	b->count++;
	if (b->count >= b->total)
	{
		b->count = 0;
		pthread_cond_broadcast(&b->cond);
		pthread_mutex_unlock(&b->lock);
		return (0);
	}
	pthread_cond_wait(&b->cond, &b->lock);
	pthread_mutex_unlock(&b->lock);
	return (0);
}



void		render_realtime(t_minirt *rt)
{
	rt->acnt = 0;
	
	//TOP DEPART
	barrier_wait(&rt->ready);

	//ON ATTEND LA FIN
	barrier_wait(&rt->done);
	
	//ON PUSH L'IMAGE A L'ECRAN
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

void		init_threads(t_minirt *rt)
{
	int				i;
	pthread_t		*threads;
	t_threadargs	*args;
	int				*returned;

	i = -1;
	threads = rt->threads;
	returned = rt->returned;
	args = rt->threadargs;
	barrier_init(&rt->ready, NB_CORES + 1);
	barrier_init(&rt->done, NB_CORES + 1);
	//DON T FORGET TO DESTROY
	while (++i < NB_CORES)
	{
		args[i].img = rt->img->imgdata;
		args[i].rt = rt;
		args[i].w = rt->world;
		args[i].id = i;
		args[i].threadstart = rt->resy * i / NB_CORES;
		args[i].threadend = (rt->resy * (i + 1) / NB_CORES);
		returned[i] = pthread_create(
					&threads[i], NULL, &thread_realtime, (void*)&args[i]);
	}
}

void		kill_threads(t_minirt *rt)
{
	int				i;
	pthread_t		*threads;

	threads = rt->threads;
	i = -1;
	while (++i < NB_CORES)
	{
		pthread_cancel(threads[i]);
		pthread_join(threads[i], NULL);
	}
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
	int				returned[NB_CORES];
	(void) returned;
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
		returned[i] = pthread_create(&threads[i],
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

int		rt_loop(t_minirt *rt)
{
	if (rt->realtime)
	{
		if (rt->keys & FORWARD)
			rt->world->currentcamera->pos = v3add(
				rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->px, MVCAMSPEED));
		if (rt->keys & BACKWARD)
			rt->world->currentcamera->pos = v3add(
				rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->px, -MVCAMSPEED));
		if (rt->keys & LEFT)
			rt->world->currentcamera->pos = v3add(
				rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->py, -MVCAMSPEED));
		if (rt->keys & RIGHT)
			rt->world->currentcamera->pos = v3add(
				rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->py, MVCAMSPEED));
		if (rt->keys & RLEFT)
			t_camera_rot_itself(rt->world->currentcamera, 0, 0, RTCAMSPEED);
		if (rt->keys & RFORWARD)
			t_camera_rot_itself(rt->world->currentcamera, 0, -RTCAMSPEED, 0);
		if (rt->keys & RRIGHT)
			t_camera_rot_itself(rt->world->currentcamera, 0, 0, -RTCAMSPEED);
		if (rt->keys & RBACKWARD)
			t_camera_rot_itself(rt->world->currentcamera, 0, RTCAMSPEED, 0);
		if (rt->keys & RROLL)
			t_camera_rot_itself(rt->world->currentcamera, RTCAMSPEED, 0, 0);
		if (rt->keys & LROLL)
			t_camera_rot_itself(rt->world->currentcamera, -RTCAMSPEED, 0, 0);
		render_realtime(rt);
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_minirt	rt;
	t_world		*w;

	write(1, "\e[1;36mSTARTING\n\e[0m", 20);
	ft_bzero(&rt, sizeof(t_minirt));
	w = world_init();
	rt.world = w;

	if (NB_CORES <= 0)
	{
		write(1, "\e[1;31mWrong core number\n\e[0m", 20);
		quit_window(&rt, -1);
	}
	if (ac != 2)
	{
		write(1, "\e[1;31mMissing an argument\n\e[0m", 31);
		quit_window(&rt, -1);
	}
	if (parse_filename(av[1]) == ERROR)
	{
		write(1, "\e[1;31mWrong filename\n\e[0m", 26);
		quit_window(&rt, -1);
	}
	if (parse_world(&rt, av[1]) == ERROR)
	{
		write(1, "\e[1;31mERROR while parsing\n\e[0m", 31);
		quit_window(&rt, -1);
	}
	if (!rt.world->ambient && add_ambient(w, 0, 0xfffffff) == ERROR)
	{
		write(1, "\e[1;31mALLOCAION ERROR\n\e[0m", 18);
		quit_window(&rt, -1);
	}
	rt.mlx = mlx_init();
	rt.sizex = rt.resx;
	rt.sizey = rt.resy;
	if ((rt.img = malloc(sizeof(t_image))) == NULL ||
		(rt.img->img = mlx_new_image(rt.mlx, rt.sizex, rt.sizey)) == NULL)
	{
		free_everything(&rt);
		write(1, "\e[1;31mALLOCAION ERROR\n\e[0m", 18);
		return (-1);
	}


	rt.img->imgdata = (unsigned int *)mlx_get_data_addr(
		rt.img->img, &rt.img->depth, &rt.img->linesize,	&rt.img->edian);
	rt.win = mlx_new_window(rt.mlx, rt.sizex, rt.sizey, "minirt");
	w->nbcameras = ft_lstsize(w->cameras);
	w->camindex = 0;
	w->currentcamera = get_camera(w->cameras, w->camindex);

	mlx_hook(rt.win, 2, 1L << 0, key_pressed, &rt);
	mlx_hook(rt.win, 3, 1L << 1, key_released, &rt);
	mlx_hook(rt.win, 17, 131072, quit_window, &rt);
	mlx_loop_hook(rt.mlx, rt_loop, &rt);
	
	
	rt.realtime = 0;

	render_static(&rt);
	mlx_loop(rt.mlx);
	quit_window(&rt, 0);
	return (0);
}
