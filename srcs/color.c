/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:27:46 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/03 18:51:40 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <color.h>

#include <stdio.h>

unsigned int	viewed_color(t_color surface, t_color light, double intensity)
{
	(void) light;
	surface.color.r = (unsigned int)((surface.color.r) * intensity);
	surface.color.g = (unsigned int)((surface.color.g) * intensity);
	surface.color.b = (unsigned int)((surface.color.b) * intensity);
	return (surface.v);
}

unsigned int	left_color(unsigned int l, vec3 albedo, double intensity)
{
	t_color c;

	t_color light ;

	light.v = l;
	(void) albedo;
	c.color.r = (unsigned int)(light.color.r * albedo.x);
	c.color.g = (unsigned int)(light.color.g * albedo.y);
	c.color.b = (unsigned int)(light.color.b * albedo.z);

	// printf("%lf %lf %lf\n", albedo.x,albedo.y,albedo.z);
	(void) intensity;
	// c.color.r = (unsigned int)(c.color.r * intensity);
	// c.color.g = (unsigned int)(c.color.g * intensity);
	// c.color.b = (unsigned int)(c.color.b * intensity);


	return (c.v);
}
