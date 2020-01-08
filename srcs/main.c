/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/08 17:43:34 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>


#include <string.h>

int main(int ac, char **av)
{
	(void) ac;
	(void) av;
	write(1, "\e[1;36mSTARTING\n\e[0m", 20);

	t_minirt rt;
	rt.mlx = mlx_init();
	if (ac == 1)
	{
		rt.resx = 1920/2;
		rt.resy = 1080/2;
	}
	else
	{
		rt.resx = 1920/4;
		rt.resy = 1080/4;
	}
	rt.frame = 0;
	if (!(rt.img = malloc(sizeof(t_image))))
		return (0);
	rt.img->img = mlx_new_image(rt.mlx,	rt.resx, rt.resy);
	rt.img->imgdata = (unsigned int *)mlx_get_data_addr(
		rt.img->img, &rt.img->depth, &rt.img->linesize,	&rt.img->edian);
	rt.win = mlx_new_window(rt.mlx, rt.resx, rt.resy, "minirt");

	t_world *w = world_init();
	rt.world = w;

	double test;
	parse_double(&test, "15 0.652");
	printf("DOUBLE: \e[1;36m%lf\n", test);

	add_sphere(w, v3new(0, 3, 0), 0.5, 0xff0000);
	add_cylinder(w, v3new(0, 0, 0), v3new(0, M_PI_2, 0), 5, 2, 0xffffff);
	add_ligth(w, v3new(0, 0, 5), 500, 0xff0000);
	add_ligth(w, v3new(1, 0, 0), 150, 0xff00);
	add_ambient(w, 0.3, 0xffffff);
	add_t_camera(w, v3new(-5, 0, 0), v3new(0, 0, 0), v3new(90, 60, 0));
	add_t_camera(w, v3new(-5, 0, 2), v3new(0, 0, 0), v3new(90, 60, 0));


	w->nbcameras = ft_lstsize(w->cameras);
	w->camindex = 0;
	t_camera_render(get_camera(w->cameras, w->camindex), rt.img->imgdata, rt.world, &rt);
	mlx_put_image_to_window(rt.mlx, rt.win, rt.img->img, 0, 0);
	mlx_key_hook(rt.win, &key_events, (void*)&rt);
	mlx_hook(rt.win, 17, 131072, quit_window, &rt);
	mlx_loop(rt.mlx);

	//FREE AS MUCH AS YOU CAN
}
 