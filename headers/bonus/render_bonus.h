/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:04:47 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/29 15:42:37 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_BONUS_H
# define RENDER_BONUS_H

# include <raytracerstruct_bonus.h>

void	render_static(t_minirt *rt);
void	*t_camera_render(void *arg);
void	render_realtime(t_minirt *rt);
void	t_camera_render_lowres(t_minirt *rt, t_camera *c, int start, int end);
void	write_block(unsigned int *img, unsigned int color,
								t_blockargs *args, int sizex);
#endif
