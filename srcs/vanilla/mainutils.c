/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mainutils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:55:56 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/25 16:22:58 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <raytracer.h>

void		check_and_parse(t_minirt *rt, int ac, char **av)
{
	t_world		*w;

	w = world_init();
	rt->world = w;
	if (NB_CORES <= 0)
	{
		write(1, "\e[1;31mWrong core number\n\e[0m", 20);
		quit_window(rt, -1);
	}
	if (ac < 2)
	{
		write(1, "\e[1;31mMissing an argument\n\e[0m", 31);
		quit_window(rt, -1);
	}
	if (parse_filename(av[1]) == ERROR)
	{
		write(1, "\e[1;31mWrong filename\n\e[0m", 26);
		quit_window(rt, -1);
	}
	if (parse_world(rt, av[1]) == ERROR)
	{
		write(1, "\e[1;31mERROR while parsing\n\e[0m", 31);
		quit_window(rt, -1);
	}
}

void		init_mlx(t_minirt *rt)
{
	rt->mlx = mlx_init();
	rt->sizex = rt->resx;
	rt->sizey = rt->resy;
	if ((rt->img = malloc(sizeof(t_image))) == NULL ||
		(rt->img->img = mlx_new_image(rt->mlx, rt->sizex, rt->sizey)) == NULL)
	{
		write(1, "\e[1;31mALLOCAION ERROR\n\e[0m", 27);
		quit_window(rt, -1);
	}
	rt->img->imgdata = (unsigned int *)mlx_get_data_addr(
		rt->img->img, &rt->img->depth, &rt->img->linesize, &rt->img->edian);
	rt->win = mlx_new_window(rt->mlx, rt->sizex, rt->sizey, "minirt");
}

int			parse_filename(char *path)
{
	char *extension;

	extension = ft_strrchr(path, '.');
	if (!extension ||
		ft_strncmp(".rt", extension, ft_max(ft_strlen(extension), 3)) != 0)
		return (ERROR);
	return (SUCCESS);
}

void		free_everything(t_minirt *rt)
{
	t_world *w;

	w = rt->world;
	if (w)
	{
		ft_lstclear(&w->lights, free);
		ft_lstclear(&w->cameras, free);
		if (w->ambient)
		{
			ft_bzero(w->ambient, sizeof(t_light));
			free(w->ambient);
		}
		if (w->obj)
			free_allobj3d(w->obj);
		free(w);
	}
	if (rt->mlx)
	{
		if (rt->img->img)
			mlx_destroy_image(rt->mlx, rt->img->img);
		free(rt->img);
		mlx_destroy_window(rt->mlx, rt->win);
	}
}
