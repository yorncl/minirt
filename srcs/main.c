/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/12 18:05:46 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>


#include <string.h>

void	camera_render(camera *c, unsigned int *img, t_world *w, t_minirt *rt)
{
	int		i;
	int		j;
	vec3	r;

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
			img[j * rt->resx + i] = ray_trace(w, c->pos, r, 1);
		}
	}
}

int		loop(t_minirt *rt)
{
	double	angle = 0.1;
	vec3	center = v3new(0, 0, 0);
	vec3	dir = v3sub(rt->world->c->pos, center);
	vec3	cp = v3cpy(dir);
	v3rotateZ(&cp, -angle);
	rt->world->c->pos = v3add(rt->world->c->pos, v3sub(dir, cp));
	camera_rot(rt->world->c, 0, 0, angle);
	camera_render(rt->world->c, rt->img->imgdata, rt->world, rt);
	mlx_put_image_to_window(rt->mlx, rt->win, rt->img->img, 0, 0);
	return (0);
}

int		move(int keycode, camera *c)
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
		raytracer.resx = 1920;
		raytracer.resy = 1080;
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

	if (ac == 1)
	{
		add_plane(w, v3new(0, 0, 0), v3new(0, 0, 0), 0x00ffffff);
		add_plane(w, v3new(0, 0, 4), v3new(0, 0, 0), 0x00ffffff);
		add_plane(w, v3new(-4, 0, 0), v3new(0, M_PI / 2, 0), 0xFF0055);
		add_plane(w, v3new(4, 0, 0), v3new(0, M_PI / 2, 0), 0x0000FF);
		add_plane(w, v3new(0, -4, 0), v3new(M_PI / 2, 0, 0), 0x00FF00);
		add_plane(w, v3new(0, 4, 0), v3new(M_PI / 2, 0, 0), 0xFF0000);
		
		
		add_sphere(w, v3new(3, -3, 1), 1, 0x00ff0000);
		add_sphere(w, v3new(0, 3, 1), 1, 0x0000FF00);
		add_sphere(w, v3new(0.5, -2.5, 0.4), 0.4, 0x00FF00FF);
		add_sphere(w, v3new(2, 3, 0.6), 0.6, 0x9922FF);
		add_sphere(w, v3new(-2, 2.5, 0.6), 0.6, 0x0000bfFF);
		add_sphere(w, v3new(0, 0, 0.7), 0.7, 0x00FFdfFF);
		add_sphere(w, v3new(-1, -3, 0.8), 0.8, 0x00Fd00FF);
		add_sphere(w, v3new(-2.2, -0.4, 0.2), 0.2, 0x00FF00FF);

		add_triangle(w, v3new(3,1, 3), v3new(4, 0, 2), v3new(2, 1, 1),0x00FF00);

		add_square(w, v3new(1, -1, 2.5), v3new(0.4, -0.8, 0), 1,0xFF0000);

		add_ligth(w, v3new(0, 0, 3), 120, 0xFFFFFF);
		add_ligth(w, v3new(3.8, 3.8, 3), 30, 0xFF00FF);
		add_ligth(w, v3new(-3.8, 3.8, 3), 150, 0xFF0000);
		add_ligth(w, v3new(-3.8, -3.8, 3), 150, 0x00FF00);
		// add_ligth(w, v3new(0, 3.8, 3), 250, 0x0000FF);
		add_camera(w, v3new(-3.5, 0, 2), v3new(0, 0, 0), v3new(90, 60, 0));
	}
	else
	{
		if (strcmp(av[1],"plane") == 0)
		{
			add_plane(w, v3new(0, 0, 1.5), v3new(M_PI / 2, 0, 0), 0xFF00FF);
		}
		if (strcmp(av[1],"square") == 0)
		{
			add_square(w, v3new(0, 0, 0), v3new(0, 0.8, 0), 10,0xFF0000);
		}
		if (strcmp(av[1],"triangle") == 0)
		{
			add_triangle(w, v3new(1,1, 0), v3new(1, 0, 2), v3new(0, 1, 0),0x00FF00);
		}
		add_ligth(w, v3new(0, 5, 2.5), 80, 0x00FFFFFF);
		add_camera(w, v3new(-2, 0, 2), v3new(0, 0.8, 0), v3new(90, 60, 0));
	}
	raytracer.world = w;
	if (ac == 1)
	{
		camera_render(w->c, raytracer.img->imgdata, raytracer.world, &raytracer);
		mlx_put_image_to_window(raytracer.mlx, raytracer.win, raytracer.img->img, 0, 0);
	}
	else
	{
		mlx_loop_hook(raytracer.mlx, &loop, &raytracer);
	//	mlx_key_hook(raytracer.mlx, &move, w->c);
	}
	mlx_loop(raytracer.mlx);
}