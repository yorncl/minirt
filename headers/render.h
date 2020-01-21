/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 15:04:47 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 15:05:29 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include <raytracerstruct.h> 

void	render_static(t_minirt *rt);
void	*t_camera_render(void *arg);
void 	render_realtime(t_minirt *rt);
void	t_camera_render_lowres(t_minirt *rt, t_camera *c, int start, int end);
#endif