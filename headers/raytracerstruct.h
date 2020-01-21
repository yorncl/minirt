

#ifndef RAYTRACERSTRUCT_H
# define RAYTRACERSTRUCT_H

#include <mlx.h>
#include <world.h>
#include <macro.h>

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

typedef struct	s_barrier
{
	pthread_cond_t	cond;
	pthread_mutex_t	lock;
	int				count;
	int				total;
}				t_barrier;

int		barrier_init(t_barrier *b, int num);
int		barrier_wait(t_barrier *b);
int		barrier_destroy(t_barrier *b);


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
	t_barrier		ready;
	t_barrier		done;
	t_world 		*world;
}				t_minirt;
#endif
