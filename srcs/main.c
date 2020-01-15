/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/15 11:47:36 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>


#include <string.h>

int		parse_filename(char *path)
{
	char *extension;

	extension = strrchr(path, '.');
	if (!extension ||
		ft_strncmp(".rt", extension, ft_max(ft_strlen(extension), 3)) != 0)
		return (ERROR);
	return (SUCCESS);
}

void	free_everything(t_minirt *rt)
{
	t_world *w;

	w = rt->world;
	if (w)
	{
		ft_lstclear(&w->lights, free);
		ft_lstclear(&w->cameras, free);
		if (w->ambient)
			ft_bzero(w->ambient, sizeof(t_light));
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























// void render_realtime(t_minirt *rt)
// {
	
// }

// void	render_slice(void *arg)
// {
// 	while (1)
// 	{
		
// 	}
	
// }

void	init_threads(t_minirt *rt)
{
	int				i;
	pthread_t		*threads;
	t_threadargs	*args;
	int				*returned;

	i = -1;
	threads = rt->threads;
	returned = rt->returned;
	args = rt->threadargs;
	while (++i < NB_CORES)
	{
		args[i].c = rt->world->currentcamera;
		args[i].img = rt->img->imgdata;
		args[i].rt = rt;
		args[i].w = rt->world;
		args[i].id = i;
		args[i].threadstart = rt->resy * i / NB_CORES ;
		args[i].threadend = rt->resy * (i + 1) / NB_CORES;
		returned[i] = pthread_create(
					&threads[i], NULL, render_slice, (void*)&args[i]);
	}
}

void	t_camera_render_lowres(t_threadargs *args)
{
	int		i;
	int		j;
	int		dx;
	int		dy;
	unsigned int color;
	(void) color;
	t_vec3	r;

	dx = args->rt->sizex / args->rt->resx;
	dy = args->rt->sizey / args->rt->resy;
	j = args->rt->resy * args->threadstart - 1;
	while (++j < args->rt->resy * args->threadend)
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
			color = ray_trace(args->w, args->c->pos, r, 3);
			for (int a = 0; a < dy; a++)
			{
				for (int b = 0; b < dx; b++)
				{
					args->img[(j * dy + a) * args->rt->sizex +
						 i * dx + b] = color; 
				}
			}
		}
	}
}

void render_static(t_minirt *rt)
{
	int				i;
	pthread_t		threads[NB_CORES];
	int				returned[NB_CORES];
	t_threadargs	args[NB_CORES];
	(void) returned;

	i = -1;
	while (++i < NB_CORES)
	{
		args[i].c = rt->world->currentcamera;
		args[i].img = rt->img->imgdata;
		args[i].rt = rt;
		args[i].w = rt->world;
		args[i].id = i;
		args[i].threadstart = rt->resy * i / NB_CORES ;
		args[i].threadend = rt->resy * (i + 1) / NB_CORES;
		returned[i] = pthread_create(&threads[i], NULL, t_camera_render, (void*) &args[i]);
	}
	i = -1;
	while (++i < NB_CORES)
		pthread_join(threads[i], NULL);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
	// printf("Rendered !\n");
}




















int		rt_loop(t_minirt *rt)
{
	if (rt->realtime)
	{
		//Z
		if (rt->keys & FORWARD)
			rt->world->currentcamera->pos = v3add(
				rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->px, MVCAMSPEED));
		//S
		if (rt->keys & BACKWARD)
			rt->world->currentcamera->pos = v3add(
				rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->px, -MVCAMSPEED));
		//Q
		if (rt->keys & LEFT)
			rt->world->currentcamera->pos = v3add(
				rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->py, -MVCAMSPEED));
		//D
		if (rt->keys & RIGHT)
			rt->world->currentcamera->pos = v3add(
				rt->world->currentcamera->pos, v3scale(rt->world->currentcamera->py, MVCAMSPEED));
		//gauche
		if (rt->keys & RLEFT)
			t_camera_rot_itself(rt->world->currentcamera, 0, 0, RTCAMSPEED);
		//haut
		if (rt->keys & RFORWARD)
			t_camera_rot_itself(rt->world->currentcamera, 0, -RTCAMSPEED, 0);
		//droite
		if (rt->keys & RRIGHT)
			t_camera_rot_itself(rt->world->currentcamera, 0, 0, -RTCAMSPEED);
		//roule
		if (rt->keys & RBACKWARD)
			t_camera_rot_itself(rt->world->currentcamera, 0, RTCAMSPEED, 0);
		if (rt->keys & RROLL)
			t_camera_rot_itself(rt->world->currentcamera, RTCAMSPEED, 0, 0);
		//ma poule
		if (rt->keys & LROLL)
			t_camera_rot_itself(rt->world->currentcamera, -RTCAMSPEED, 0, 0);
		// t_camera_render_lowres(rt->world->currentcamera, rt->img->imgdata, rt->world, rt);
		// mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
		render_realtime(rt);
	}
	return (0);
}

int		main(int ac, char **av)
{
	t_minirt	rt;
	t_world		*w;

	write(1, "\e[1;36mSTARTING\n\e[0m", 20);
	ft_bzero(&rt, sizeof(t_minirt));
	w = world_init();
	rt.world = w;
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

	mlx_hook(rt.win, 2, 1L<<0, key_pressed, &rt);
	mlx_hook(rt.win, 3, 1L<<1, key_released, &rt);
	mlx_hook(rt.win, 17, 131072, quit_window, &rt);
	mlx_loop_hook(rt.mlx, rt_loop, &rt);
	
	
	rt.realtime = 0;
	printf("1 img addr: %p\n", rt.img->img);

	render_static(&rt);
	printf("3 img addr: %p\n", rt.img->img);
	mlx_loop(rt.mlx);
	quit_window(&rt, 0);
	return (0);
}
