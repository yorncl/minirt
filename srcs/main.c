/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 14:59:38 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void		handle_pos(t_minirt *rt)
{
	if (rt->keys & FORWARD)
		rt->world->currentcamera->pos = v3add(rt->world->currentcamera->pos,
			v3scale(rt->world->currentcamera->px, MVCAMSPEED));
	if (rt->keys & BACKWARD)
		rt->world->currentcamera->pos = v3add(rt->world->currentcamera->pos,
			v3scale(rt->world->currentcamera->px, -MVCAMSPEED));
	if (rt->keys & LEFT)
		rt->world->currentcamera->pos = v3add(rt->world->currentcamera->pos,
			v3scale(rt->world->currentcamera->py, -MVCAMSPEED));
	if (rt->keys & RIGHT)
		rt->world->currentcamera->pos = v3add(rt->world->currentcamera->pos,
			v3scale(rt->world->currentcamera->py, MVCAMSPEED));
	if (rt->keys & RLEFT)
		t_camera_rot_itself(rt->world->currentcamera, 0, 0, RTCAMSPEED);
}

void		handle_rot(t_minirt *rt)
{
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
}

int			rt_loop(t_minirt *rt)
{
	if (rt->realtime)
	{
		handle_pos(rt);
		handle_rot(rt);
		render_realtime(rt);
	}
	return (0);
}

int			main(int ac, char **av)
{
	t_minirt	rt;

	write(1, "\e[1;36mSTARTING\n\e[0m", 20);
	ft_bzero(&rt, sizeof(t_minirt));
	check_and_parse(&rt, ac, av);
	if (!rt.world->ambient && add_ambient(rt.world, 0, 0xfffffff) == ERROR)
	{
		write(1, "\e[1;31mALLOCAION ERROR\n\e[0m", 18);
		quit_window(&rt, -1);
	}
	rt.world->nbcameras = ft_lstsize(rt.world->cameras);
	rt.world->camindex = 0;
	rt.world->currentcamera = get_camera(rt.world->cameras, rt.world->camindex);
	init_mlx(&rt);
	mlx_hook(rt.win, 2, 1L << 0, key_pressed, &rt);
	mlx_hook(rt.win, 3, 1L << 1, key_released, &rt);
	mlx_hook(rt.win, 17, 131072, quit_window, &rt);
	mlx_loop_hook(rt.mlx, rt_loop, &rt);
	rt.realtime = 0;
	render_static(&rt);
	if (ac == 3 && ft_strncmp("-save", av[2],ft_strlen(av[2])) == 0)
	{
		write_bmp(&rt, "save1.bmp");
		save_first_frame(&rt, "save2.bmp");
		quit_window(&rt, 0);
	}
	mlx_loop(rt.mlx);
	quit_window(&rt, 0);
	return (0);
}
