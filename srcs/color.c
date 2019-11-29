/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 14:27:46 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/29 15:32:56 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <color.h>

unsigned int	viewed_color(t_color surface, t_color light, double intensity)
{
	(void) light;
	surface.color.r = (unsigned int)((surface.color.r) * intensity);
	surface.color.g = (unsigned int)((surface.color.g) * intensity);
	surface.color.b = (unsigned int)((surface.color.b) * intensity);
	return (surface.v);
}