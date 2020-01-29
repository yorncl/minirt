/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   barrier_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:51:52 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/29 14:38:30 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <threads_bonus.h>

int		barrier_init(t_barrier *b, int num)
{
	if (num == 0)
		return (-1);
	if (pthread_mutex_init(&b->lock, 0) < 0)
		return (-1);
	if (pthread_cond_init(&b->cond, 0) < 0)
	{
		pthread_mutex_init(&b->lock, 0);
		return (-1);
	}
	b->total = num;
	b->count = 0;
	return (0);
}

int		barrier_destroy(t_barrier *b)
{
	pthread_cond_destroy(&b->cond);
	pthread_mutex_destroy(&b->lock);
	return (0);
}

int		barrier_wait(t_barrier *b)
{
	pthread_mutex_lock(&b->lock);
	b->count++;
	if (b->count >= b->total)
	{
		b->count = 0;
		pthread_cond_broadcast(&b->cond);
		pthread_mutex_unlock(&b->lock);
		return (0);
	}
	pthread_cond_wait(&b->cond, &b->lock);
	pthread_mutex_unlock(&b->lock);
	return (0);
}
