/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:56:38 by marvin            #+#    #+#             */
/*   Updated: 2019/11/23 18:56:38 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

# include <math.h>
# include <stdlib.h>

typedef struct	s_vec3
{
	double x;
	double y;
	double z;
}				vec3;

vec3	*v3new(double x, double y, double z);
void	v3set(vec3 *v, double x, double y, double z);

/*
**	Operations
*/
void	v3add(vec3 *a, vec3 *b);
void	v3add3(vec3 *a, double x, double y, double z);
void	v3sub(vec3 *a, vec3 *b);
void	v3sub3(vec3 *a, double x, double y, double z);
/*
**	Multiplication
*/
void	v3scale(vec3 *v, double s);
vec3	*v3cross(vec3 *a, vec3 *b);
double	v3dot(vec3 *a, vec3 *b);
/*
**	Rotation
*/
void	v3rotate(vec3 *a, vec3 *b);
void	v3rotate3(vec3 *v, double x, double y, double z);
void	v3rotateX(vec3 *v, double o);
void	v3rotateY(vec3 *v, double o);
void	v3rotateZ(vec3 *v, double o);
#endif
