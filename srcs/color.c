/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:27:46 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/21 17:53:57 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <color.h>

unsigned int	viewed_color(t_color surface, t_color light, double intensity)
{
	(void)light;
	surface.color.r = (unsigned int)((surface.color.r) * intensity);
	surface.color.g = (unsigned int)((surface.color.g) * intensity);
	surface.color.b = (unsigned int)((surface.color.b) * intensity);
	return (surface.v);
}

unsigned int	left_color(unsigned int l, t_vec3 albedo, double intensity)
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

t_color			colormultiplyf(t_color c, double coef)
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

t_color			colormultiplyv3(t_color c, t_vec3 v)
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

t_color			coloradd(t_color c1, t_color c2)
{
	unsigned int	tmp;
	t_color			new;

	new.v = 0;
	tmp = c1.color.r + c2.color.r;
	new.color.r = tmp > 255 ? 255 : tmp;
	tmp = c1.color.g + c2.color.g;
	new.color.g = tmp > 255 ? 255 : tmp;
	tmp = c1.color.b + c2.color.b;
	new.color.b = tmp > 255 ? 255 : tmp;
	return (new);
}
