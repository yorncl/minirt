/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 10:53:14 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/15 16:43:14 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

int		key_pressed(int keycode, t_minirt *rt)
{
	//Q
	if (keycode == KEY_A)
		rt->keys |= LEFT;
	//Z
	if (keycode == KEY_W)
		rt->keys |= FORWARD;
	//D
	if (keycode == KEY_D)
		rt->keys |= RIGHT;
	//S
	if (keycode == KEY_S)
		rt->keys |= BACKWARD;
	//LEFT
	if (keycode == KEY_LEFT)
		rt->keys |= RLEFT;
	//UP
	if (keycode == KEY_UP)
		rt->keys |= RFORWARD;
	//RIGHT
	if (keycode == KEY_RIGHT)
		rt->keys |= RRIGHT;
	//DOWN
	if (keycode == KEY_DOWN)
		rt->keys |= RBACKWARD;
	//A
	if (keycode == KEY_Q)
		rt->keys |= RROLL;
	//E
	if (keycode == KEY_E)
		rt->keys |= LROLL;
	printf("%d\n", keycode);
	return (0);
}

int		key_released(int keycode, t_minirt *rt)
{
	//Q
	if (keycode == KEY_A)
		rt->keys ^= LEFT;
	//Z
	if (keycode == KEY_W)
		rt->keys ^= FORWARD;
	//D
	if (keycode == KEY_D)
		rt->keys ^= RIGHT;
	//S
	if (keycode == KEY_S)
		rt->keys ^= BACKWARD;
	//LEFT
	if (keycode == KEY_LEFT)
		rt->keys ^= RLEFT;
	//UP
	if (keycode == KEY_UP)
		rt->keys ^= RFORWARD;
	//RIGHT
	if (keycode == KEY_RIGHT)
		rt->keys ^= RRIGHT;
	//DOWN
	if (keycode == KEY_DOWN)
		rt->keys ^= RBACKWARD;
	//A
	if (keycode == KEY_Q)
		rt->keys ^= RROLL;
	//E
	if (keycode == KEY_E)
		rt->keys ^= LROLL;
	if (keycode == KEY_R)
	{
		rt->realtime = !rt->realtime;
		if (!rt->realtime)
		{
			render_realtime(rt);
			kill_threads(rt);
			rt->resx = rt->sizex;
			rt->resy = rt->sizey;
			render_static(rt);
		}
		else
		{
			rt->resx /= 7;
			rt->resy /= 7;
			init_threads(rt);
		}
	}
	if (keycode == KEY_Z || keycode == KEY_X)
		change_camera(keycode, rt);
	if (keycode == 53)
		quit_window(rt, 0);
	return (0);
}