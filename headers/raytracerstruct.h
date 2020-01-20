

#ifndef RAYTRACERSTRUCT_H
# define RAYTRACERSTRUCT_H

#include <mlx.h>
#include <world.h>
#include <macro.h>
#include <stdatomic.h>

typedef struct s_threadargs t_threadargs;

typedef struct	s_image
{
	void			*img;
	unsigned int	*imgdata;
	int				depth;
	int				linesize;
	int				edian;
}				t_image;
typedef struct s_threadargs
{
	t_camera		*c;
	unsigned int	*img;
	t_world			*w;
	void			*rt;
	int				threadstart;
	int				threadend;
	int				id;
}				t_threadargs;

typedef struct s_minirt
{
	void			*mlx;
	void			*win;
	t_image 		*img;
	int				resx;
	int				resy;
	int				sizex;
	int				sizey;
	int				keys;
	int 			realtime;
	pthread_t		threads[NB_CORES];
	int				returned[NB_CORES];
	t_threadargs	threadargs[NB_CORES];
	atomic_int		acnt;
	pthread_cond_t	taskstart;
	pthread_cond_t	taskdone;
	pthread_mutex_t lock;
	t_world 		*world;
}				t_minirt;
#endif
