/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 23:20:58 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 23:20:58 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void	camera_render(camera *c, unsigned int *img, t_world *w, t_minirt *rt)
{
	int i;
	int j;
	vec3 r;

	j = -1;
	while (++j < rt->resy)
	{
		i = -1;
		while (++i < rt->resx)
		{
			r.x = c->px->x - c->py->x - c->pz->x + (2 * i * c->py->x / rt->resx) + (2 * j * c->pz->x / rt->resy);
			r.y = c->px->y - c->py->y - c->pz->y + (2 * i * c->py->y / rt->resx) + (2 * j * c->pz->y / rt->resy);
			r.z = c->px->z - c->py->z - c->pz->z + (2 * i * c->py->z / rt->resx) + (2 * j * c->pz->z / rt->resy);
			img[j * rt->resx + i] = ray_trace(c, w, &r);
		}
	}
}

int main()
{
	t_minirt raytracer;

	raytracer.mlx = mlx_init();
	raytracer.resx = 1024;
	raytracer.resy = 576;
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
	printf("Image summary:\n\taddr: %p\n\tdepth: %d\n\tlinesize: %d\n\tedian: %d\n\t",raytracer.img->imgdata , raytracer.img->depth,raytracer.img->linesize,raytracer.img->edian);
	raytracer.win = mlx_new_window(raytracer.mlx, raytracer.resx, raytracer.resy, "Ma window");

	t_world w;
	w.c = camera_create();
	camera_init_pos(w.c,0,0,0);
	camera_init_vectors(w.c, 90,60);
	camera_rot(w.c, 0, 0 ,0);
	
	
	obj3d mysphere2;
	mysphere2.pos = v3new(3,0,0);
	mysphere2.type = SPHERE;
	mysphere2.color = 0x00FF1493;
	mysphere2.next = NULL;
	mysphere2.w = 1;

	obj3d mysphere;
	mysphere.pos = v3new(5,2,0);
	mysphere.type = SPHERE;
	mysphere.color = 0x00C71585;
	mysphere.next = &mysphere2;
	mysphere.w = 1;
	w.obj = &mysphere;

	
	raytracer.world = &w;

	camera_render(w.c, raytracer.img->imgdata, raytracer.world, &raytracer);
	
	mlx_put_image_to_window(raytracer.mlx, raytracer.win, raytracer.img->img, 0, 0);
	mlx_loop(raytracer.mlx);
}