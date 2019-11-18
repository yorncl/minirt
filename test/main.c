#include <mlx.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <limits.h>

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
}				t_minirt;

int f(void *raytracer)
{
	int				x;
	int				y;
	t_minirt		*ptr;
	unsigned int	val;

	ptr = raytracer;
	val = 16711680;
	y = -1;
	while (++y < ptr->resy)
	{
		x = -1;
		while (++x < ptr->resx)
		{
			if ((x - 150 < ptr->resx / 2 && x + 150 > ptr->resx / 2) && (y - 150 < ptr->resy / 2 && y + 150 > ptr->resy / 2))
				ptr->img->imgdata[x + y * ptr->resx] =  val + cosf((x + ptr->frame)/15) * 10000;
			else if ((x - 300 < ptr->resx / 2 && x + 300 > ptr->resx / 2) &&  y > -10 * x + ptr->resy / 2)
				ptr->img->imgdata[x + y * ptr->resx] =  (x + ptr->frame) + (y + ptr->frame);
			else
				ptr->img->imgdata[x + y * ptr->resx] =  (x + ptr->frame) * 100 + (y + ptr->frame) * 100;
		}
	}
	ptr->frame++;
	mlx_put_image_to_window(ptr->mlx, ptr->win, ptr->img->img, 0, 0);
	return (0);
}

int main()
{
	t_minirt raytracer;

	raytracer.mlx = mlx_init();
	raytracer.resx = 1920;
	raytracer.resy = 1080;
	raytracer.frame = 0;
	if (!(raytracer.img = malloc(sizeof(t_image))))
		return (0);
	raytracer.img->img = mlx_new_image(raytracer.mlx,
		raytracer.resx,
		raytracer.resy);
	raytracer.img->imgdata = (unsigned int *)mlx_get_data_addr(
		raytracer.img->img,
		&raytracer.img->depth,
		&raytracer.img->linesize,
		&raytracer.img->edian);
	//CHECK IF DIMENSIONS ARE RIGHT
	printf("Iamge summary:\n\taddr: %p\n\tdepth: %d\n\tlinesize: %d\n\tedian: %d\n\t",raytracer.img->imgdata , raytracer.img->depth,raytracer.img->linesize,raytracer.img->edian);
	raytracer.win = mlx_new_window(raytracer.mlx, raytracer.resx, raytracer.resy, "Ma window");
	mlx_loop_hook(raytracer.mlx, &f, &raytracer);
	mlx_loop(raytracer.mlx);
}