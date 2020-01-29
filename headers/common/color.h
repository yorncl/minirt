/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:24:25 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/22 11:46:08 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COLOR_H
# define COLOR_H

# include <vec3.h>

typedef union		u_color
{
	unsigned int	v;
	struct			s_color
	{
		unsigned int b : 8;
		unsigned int g : 8;
		unsigned int r : 8;
		unsigned int a : 8;
	}				color;
}					t_color;

unsigned int		viewed_color(t_color surface, t_color light,
													double intensity);
unsigned int		left_color(unsigned intlight, t_vec3 albedo,
													double intensity);
t_color				colormultiplyf(t_color c, double coef);
t_color				colormultiplyv3(t_color c, t_vec3 v);
t_color				coloradd(t_color c1, t_color c2);
#endif
