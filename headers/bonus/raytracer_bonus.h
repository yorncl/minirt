/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracer_bonus.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:22 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/29 14:57:37 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACER_BONUS_H
# define RAYTRACER_BONUS_H

# include <mlx.h>
# include <render.h>
# include <threads_bonus.h>
# include <parser.h>
# include <math.h>
# include <stdlib.h>
# include <limits.h>
# include <camera.h>
# include <raytracerstruct.h>
# include <world.h>
# include <ray.h>
# include <bmpsave.h>

# define KEY_A 		0
# define KEY_W 		13
# define KEY_D 		2
# define KEY_S 		1
# define KEY_LEFT 	123
# define KEY_UP 	126
# define KEY_RIGHT 	124
# define KEY_DOWN	125
# define KEY_Q		12
# define KEY_E		14
# define KEY_R		15
# define KEY_Z		6
# define KEY_X		7
# define KEY_ESCAPE	53

/*
**	events
*/
int		key_events(int keycode, t_minirt *raytracer);
int		key_pressed(int keycode, t_minirt *rt);
int		key_released(int keycode, t_minirt *rt);
void	toggle_realtime(t_minirt *rt);
int		quit_window(t_minirt *rt, int code);
int		change_camera(int keycode, t_minirt *raytracer);

/*
**	utils
*/
void	check_and_parse(t_minirt *rt, int ac, char **av);
void	init_mlx(t_minirt *rt);
int		parse_filename(char *path);
void	free_everything(t_minirt *rt);
void	save_and_exit(t_minirt *rt);
#endif
