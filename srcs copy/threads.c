/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:47:03 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 15:02:46 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <threads.h>

void		init_threads(t_minirt *rt)
{
	int				i;
	pthread_t		*threads;
	t_threadargs	*args;
	int				*returned;

	i = -1;
	threads = rt->threads;
	returned = rt->returned;
	args = rt->threadargs;
	barrier_init(&rt->ready, NB_CORES + 1);
	barrier_init(&rt->done, NB_CORES + 1);
	while (++i < NB_CORES)
	{
		args[i].img = rt->img->imgdata;
		args[i].rt = rt;
		args[i].w = rt->world;
		args[i].id = i;
		args[i].threadstart = rt->resy * i / NB_CORES;
		args[i].threadend = (rt->resy * (i + 1) / NB_CORES);
		returned[i] = pthread_create(
					&threads[i], NULL, &thread_realtime, (void*)&args[i]);
	}
}

void		kill_threads(t_minirt *rt)
{
	int				i;
	pthread_t		*threads;

	threads = rt->threads;
	i = -1;
	barrier_destroy(&rt->ready);
	barrier_destroy(&rt->done);
	while (++i < NB_CORES)
	{
		pthread_cancel(threads[i]);
		pthread_join(threads[i], NULL);
	}
}
