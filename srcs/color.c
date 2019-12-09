/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:27:46 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/09 17:19:15 by mclaudel         ###   ########.fr       */
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

	c.v = l;
	c.color.r = (unsigned int)(c.color.r * albedo.x);
	c.color.g = (unsigned int)(c.color.g * albedo.y);
	c.color.b = (unsigned int)(c.color.b * albedo.z);
	c.color.r = (unsigned int)(c.color.r * intensity);
	c.color.g = (unsigned int)(c.color.g * intensity);
	c.color.b = (unsigned int)(c.color.b * intensity);
	return (c.v);
}

t_color		colormultiplyf(t_color c, double coef)
{
	unsigned int	tmp;

	tmp = (unsigned int)(c.color.r * coef);
	c.color.r = tmp > 255 ? 255 : tmp;
	tmp = (unsigned int)(c.color.g * coef);
	c.color.g = tmp > 255 ? 255 : tmp;
	tmp = (unsigned int)(c.color.b * coef);
	c.color.b = tmp > 255 ? 255 : tmp;
	return (c);
}

t_color		colormultiplyv3(t_color c, vec3 v)
{
	unsigned int	tmp;

	tmp = (unsigned int)(c.color.r * v.x);
	c.color.r = tmp > 255 ? 255 : tmp;
	tmp = (unsigned int)(c.color.g * v.y);
	c.color.g = tmp > 255 ? 255 : tmp;
	tmp = (unsigned int)(c.color.b * v.z);
	c.color.b = tmp > 255 ? 255 : tmp;
	return (c);
}
