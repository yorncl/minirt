/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 15:21:04 by mclaudel          #+#    #+#             */
/*   Updated: 2019/12/03 17:30:41 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

# include <stdlib.h>
# include <vec3.h>
# include <color.h>
/*
**	A material structure
**
**	Items refers to physical properties
**	albedo - refers to the amount of light absorbed
**	refractive - refers to the amount of light refracted [0;1] 
**	refractiveindex - the refraction index of the material
**	specular - refers to the amount of light directly reflected [0;1]
**	diffuse - refers to the amount of light diffused [0;1]
**		(in random directions through Monte Carlo integration)
**	Energy conservation rule says that refractive + diffuse + specular = 1
*/
typedef struct	s_material
{
	vec3   albedo;
	double refractive;
	double refractionindex;
	double specular;
	double diffuse;
}				t_material;

t_material		*create_material(unsigned int color, double roughness, double metallic);
# endif
