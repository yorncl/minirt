/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracerstruct.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:37:04 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/25 18:36:22 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACERSTRUCT_H
# define RAYTRACERSTRUCT_H

# include <mlx.h>
# include <world.h>
# include <macro.h>
# include <pthread.h>

typedef struct	s_image
{
	void			*img;
	unsigned int	*imgdata;
	int				depth;
	int				linesize;
	int				edian;
}				t_image;
typedef struct	s_threadargs
{
	t_camera		*c;
	unsigned int	*img;
	t_world			*w;
	void			*rt;
	int				threadstart;
	int				threadend;
	int				id;
}				t_threadargs;

typedef struct	s_blockargs
{
	int		j;
	int		i;
	double	dx;
	double	dy;
}				t_blockargs;

typedef struct	s_barrier
{
	pthread_cond_t	cond;
	pthread_mutex_t	lock;
	int				count;
	int				total;
}				t_barrier;

typedef struct	s_minirt
{
	void			*mlx;
	void			*win;
	t_image			*img;
	int				resx;
	int				resy;
	unsigned int	sizex;
	unsigned int	sizey;
	int				keys;
	int				realtime;
	pthread_t		threads[NB_CORES];
	int				returned[NB_CORES];
	t_threadargs	threadargs[NB_CORES];
	t_barrier		ready;
	t_barrier		done;
	t_world			*world;
}				t_minirt;
#endif
