/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 14:48:44 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/29 13:19:37 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef THREADS_H
# define THREADS_H

# include <raytracerstruct.h>
# include <render.h>
# include <pthread.h>

void		init_threads(t_minirt *rt);
void		kill_threads(t_minirt *rt);
void		*thread_realtime(void *arg);

int			barrier_init(t_barrier *b, int num);
int			barrier_destroy(t_barrier *b);
int			barrier_wait(t_barrier *b);
#endif
