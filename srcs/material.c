/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:52:20 by mclaudel          #+#    #+#             */
/*   Updated: 2020/01/07 16:41:39 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <material.h>

#include <stdio.h>

t_material		*create_material(
	unsigned int color,
	double roughness,
	double metallic)
{
	t_material	*m;
	t_color		c;

	m = malloc(sizeof(t_material));
	if (m == NULL)
		return (NULL);
	c.v = color;
	m->albedo.x = c.color.r / 0xff * (1 - metallic);
	m->albedo.y = c.color.g / 0xff * (1 - metallic);
	m->albedo.z = c.color.b / 0xff * (1 - metallic);
	m->refractive = 0; //Maybe later ?
	m->refractionindex = 0; //Maybe later ?
	m->specular = 1 - roughness;
	m->diffuse = roughness;
	return (m);
}
