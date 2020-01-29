/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyevents_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 10:53:14 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/29 14:54:45 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer_bonus.h>

int		key_pressed(int keycode, t_minirt *rt)
{
	if (keycode == KEY_A)
		rt->keys |= LEFT;
	if (keycode == KEY_W)
		rt->keys |= FORWARD;
	if (keycode == KEY_D)
		rt->keys |= RIGHT;
	if (keycode == KEY_S)
		rt->keys |= BACKWARD;
	if (keycode == KEY_LEFT)
		rt->keys |= RLEFT;
	if (keycode == KEY_UP)
		rt->keys |= RFORWARD;
	if (keycode == KEY_RIGHT)
		rt->keys |= RRIGHT;
	if (keycode == KEY_DOWN)
		rt->keys |= RBACKWARD;
	if (keycode == KEY_Q)
		rt->keys |= RROLL;
	if (keycode == KEY_E)
		rt->keys |= LROLL;
	if (keycode == KEY_Z || keycode == KEY_X)
		change_camera(keycode, rt);
	return (0);
}

int		key_released(int keycode, t_minirt *rt)
{
	if (keycode == KEY_A)
		rt->keys ^= LEFT;
	if (keycode == KEY_W)
		rt->keys ^= FORWARD;
	if (keycode == KEY_D)
		rt->keys ^= RIGHT;
	if (keycode == KEY_S)
		rt->keys ^= BACKWARD;
	if (keycode == KEY_LEFT)
		rt->keys ^= RLEFT;
	if (keycode == KEY_UP)
		rt->keys ^= RFORWARD;
	if (keycode == KEY_RIGHT)
		rt->keys ^= RRIGHT;
	if (keycode == KEY_DOWN)
		rt->keys ^= RBACKWARD;
	if (keycode == KEY_Q)
		rt->keys ^= RROLL;
	if (keycode == KEY_E)
		rt->keys ^= LROLL;
	if (keycode == KEY_R)
		toggle_realtime(rt);
	if (keycode == 53)
		quit_window(rt, 0);
	return (0);
}

void	toggle_realtime(t_minirt *rt)
{
	rt->realtime = !rt->realtime;
	if (!rt->realtime)
	{
		kill_threads(rt);
		rt->resx = rt->sizex;
		rt->resy = rt->sizey;
		render_static(rt);
	}
	else
	{
		if (rt->resx * rt->resy > 150 * 150)
		{
			rt->resx /= 10;
			rt->resy /= 10;
		}
		init_threads(rt);
	}
}
