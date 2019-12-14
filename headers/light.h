/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 15:04:24 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/14 14:36:38 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIGHT_H
# define LIGHT_H

# include <vec3.h>
# include <color.h>

typedef struct	s_light
{
	t_vec3			pos;
	t_color			color;
	double			intensity;
}				t_light;

t_color			direct_lightning(t_light *l, t_vec3 p, t_vec3 albedo, double ratio);
#endif