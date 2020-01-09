

#ifndef RAYTRACERSTRUCT_H
# define RAYTRACERSTRUCT_H

#include <mlx.h>
#include <world.h>

typedef struct	s_image
{
	void			*img;
	unsigned int	*imgdata;
	int				depth;
	int				linesize;
	int				edian;
}				t_image;

typedef struct s_minirt
{
	void	*mlx;
	void	*win;
	t_image *img;
	int		resx;
	int		resy;
	int		frame;
	t_world *world;
}				t_minirt;

#endif
