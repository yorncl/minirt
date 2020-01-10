/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/10 15:20:33 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>


#include <string.h>

int main(int ac, char **av)
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
		return (0);
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
}
 