/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/13 17:12:03 by mclaudel         ###   ########.fr       */
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

void	t_camera_render_lowres(t_camera *c, unsigned int *img,
							t_world *w, t_minirt *rt)
{
	int		i;
	int		j;
	int		dx;
	int		dy;
	unsigned int color;
	(void) color;
	t_vec3	r;

	rt->resx = 160;
	rt->resy = 90;
	dx = rt->sizex / rt->resx;
	dy = rt->sizey / rt->resy;
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
			color = ray_trace(w, c->pos, r, 3);
			for (int a = 0; a < dy; a++)
			{
				for (int b = 0; b < dx; b++)
				{
					img[(j * dy + a) * rt->sizex +
						 i * dx + b] = color; 
				}
			}
		}
	}
}


int		rt_loop(t_minirt *rt)
{
	if (rt->realtime)
	{
		t_camera_render_lowres(rt->world->currentcamera, rt->img->imgdata, rt->world, rt);
		mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
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
	if ((rt.img = malloc(sizeof(t_image))) == NULL ||
		(rt.img->img = mlx_new_image(rt.mlx, rt.resx, rt.resy)) == NULL)
	{
		free_everything(&rt);
		write(1, "\e[1;31mALLOCAION ERROR\n\e[0m", 18);
		return (-1);
	}

	rt.sizex = rt.resx;
	rt.sizey = rt.resy;
	rt.realtime = 0;

	rt.img->imgdata = (unsigned int *)mlx_get_data_addr(
		rt.img->img, &rt.img->depth, &rt.img->linesize,	&rt.img->edian);
	rt.win = mlx_new_window(rt.mlx, rt.sizex, rt.sizey, "minirt");
	w->nbcameras = ft_lstsize(w->cameras);
	w->camindex = 0;
	w->currentcamera = get_camera(w->cameras, w->camindex);
	t_camera_render(w->currentcamera, rt.img->imgdata, rt.world, &rt);
	mlx_put_image_to_window(rt.mlx, rt.win, rt.img->img, 0, 0);
	mlx_key_hook(rt.win, &key_events, (void*)&rt);
	mlx_hook(rt.win, 17, 131072, quit_window, &rt);

	mlx_loop_hook(rt.mlx, rt_loop, &rt);
	
	mlx_loop(rt.mlx);
	quit_window(&rt, 0);
	return (0);
}
