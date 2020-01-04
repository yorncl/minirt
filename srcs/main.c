/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/16 15:29:04 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>


#include <string.h>

void	t_camera_render(t_camera *c, unsigned int *img, t_world *w, t_minirt *rt)
{
	int		i;
	int		j;
	t_vec3	r;

	j = -1;
	while (++j < rt->resy)
	{
		i = -1;
		while (++i < rt->resx)
		{
			r.x = c->px.x - c->py.x - c->pz.x +
				(2 * i * c->py.x / rt->resx) + (2 * j * c->pz.x / rt->resy);
			r.y = c->px.y - c->py.y - c->pz.y +
				(2 * i * c->py.y / rt->resx) + (2 * j * c->pz.y / rt->resy);
			r.z = c->px.z - c->py.z - c->pz.z +
				(2 * i * c->py.z / rt->resx) + (2 * j * c->pz.z / rt->resy);
			img[j * rt->resx + i] = ray_trace(w, c->pos, r, 3);
		}
	}
}

int		loop(t_minirt *rt)
{
	double	angle = 0.1;
	t_vec3	center = v3new(0, 0, 0);
	t_vec3	dir = v3sub(rt->world->c->pos, center);
	t_vec3	cp = v3cpy(dir);
	v3rotatez(&cp, -angle);
	rt->world->c->pos = v3add(rt->world->c->pos, v3sub(dir, cp));
	t_camera_rot(rt->world->c, 0, 0, angle);
	t_camera_render(rt->world->c, rt->img->imgdata, rt->world, rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
	return (0);
}

int		move(int keycode, t_camera *c)
{
	if (keycode == 'd')
		c->pos = v3add(c->pos, c->py);
	if (keycode == 'q')
		c->pos = v3sub(c->pos, c->py);
	return (0);
}

int main(int ac, char **av)
{
	(void) ac;
	(void) av;

	t_minirt raytracer;
	raytracer.mlx = mlx_init();
	
	if (ac == 1)
	{
		raytracer.resx = 1920/2;
		raytracer.resy = 1080/2;
	}
	else
	{
		raytracer.resx = 1920/4;
		raytracer.resy = 1080/4;
	}
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
	printf("Image summary:\n\taddr: %p\n\tdepth: %d\n\tlinesize: %d\n\tedian: %d\n",raytracer.img->imgdata , raytracer.img->depth,raytracer.img->linesize,raytracer.img->edian);
	raytracer.win = mlx_new_window(raytracer.mlx, raytracer.resx, raytracer.resy, "Ma window");

	t_world *w = world_init();
	raytracer.world = w;

	double test;

	parse_double(&test, "15 0.652");
	printf("DOUBLE: %lf\n", test);
	// if (ac == 1)
	// {
		// add_sphere(w, v3new(0, 0, 0), 0.5, 0xff0000);
		add_cylinder(w, v3new(0, 0, 0), v3new(0, 0, 0), 0.5, 1, 0xffffff);
		add_ligth(w, v3new(-5, 0, 5), 600, 0xff0000);
		add_ambient(w, 0, 0xffffff);
		add_t_camera(w, v3new(-5, 0, 0), v3new(0, 0, 0), v3new(90, 60, 0));
		t_camera_render(w->c, raytracer.img->imgdata, raytracer.world, &raytracer);
		mlx_put_image_to_window(raytracer.mlx, raytracer.win, raytracer.img->img, 0, 0);
	// }
	// else
	// {
	// 	mlx_loop_hook(raytracer.mlx, &loop, &raytracer);
	// //	mlx_key_hook(raytracer.mlx, &move, w->c);
	// }
	mlx_loop(raytracer.mlx);
}