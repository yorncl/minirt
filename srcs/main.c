/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/13 16:08:21 by mclaudel         ###   ########.fr       */
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


void	free_eveything(t_minirt *rt)
{
	t_world *w;

	w = rt->world;
	ft_lstclear(w->lights, ft_bzero);
	ft_lstclear(w->cameras, ft_bzero);

	mlx_destroy_image(rt->mlx, rt->img->img);
	free(rt->img);
	mlx_destroy_window(rt->mlx, rt->win);
	free(w);
}

int		main(int ac, char **av)
{
	t_minirt rt;

	write(1, "\e[1;36mSTARTING\n\e[0m", 20);
	t_world *w = world_init();
	rt.world = w;
	if (ac != 2)
	{
		write(1, "\e[1;31mMissing an argument\n\e[0m", 31);
		return (-1);
	}
	if (parse_filename(av[1]) == ERROR)
	{
		write(1, "\e[1;31mWrong filename\n\e[0m", 26);
		return (-1);
	}
	if (parse_world(&rt, av[1]) == ERROR)
	{
		write(1, "\e[1;31mERROR while parsing\n\e[0m", 31);
		return (-1);
	}
	if (!rt.world->ambient)
		add_ambient(w, 0, 0xfffffff);

	rt.mlx = mlx_init();
	rt.frame = 0;
	if (!(rt.img = malloc(sizeof(t_image))))
		return (-1);
	//check if null
	rt.img->img = mlx_new_image(rt.mlx,	rt.resx, rt.resy);
	rt.img->imgdata = (unsigned int *)mlx_get_data_addr(
		rt.img->img, &rt.img->depth, &rt.img->linesize,	&rt.img->edian);
	rt.win = mlx_new_window(rt.mlx, rt.resx, rt.resy, "minirt");


	w->nbcameras = ft_lstsize(w->cameras);
	w->camindex = 0;
	t_camera_render(get_camera(w->cameras, w->camindex), rt.img->imgdata, rt.world, &rt);
	mlx_put_image_to_window(rt.mlx, rt.win, rt.img->img, 0, 0);
	mlx_key_hook(rt.win, &key_events, (void*)&rt);
	mlx_hook(rt.win, 17, 131072, quit_window, &rt);
	mlx_loop(rt.mlx);

	//FREE AS MUCH AS YOU CAN
	return (0);
}
 