/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 18:56:38 by marvin            #+#    #+#             */
/*   Updated: 2019/12/14 15:04:06 by mclaudel         ###   ########.fr       */
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
}				t_vec3;

t_vec3			v3new(double x, double y, double z);
t_vec3			v3cpy(t_vec3 v);
void			v3set(t_vec3 *v, double x, double y, double z);
double			v3magnitude(t_vec3 v);
t_vec3			v3normalize(t_vec3 v);
t_vec3			v3minus(t_vec3 v);
/*
**	Operations
*/
t_vec3			v3add(t_vec3 a, t_vec3 b);
t_vec3			v3add3(t_vec3 a, double x, double y, double z);
t_vec3			v3sub(t_vec3 a, t_vec3 b);
t_vec3			v3sub3(t_vec3 a, double x, double y, double z);
/*
**	Multiplication
*/
t_vec3			v3scale(t_vec3 v, double s);
t_vec3			v3cross(t_vec3 a, t_vec3 b);
double			v3dot(t_vec3 a, t_vec3 b);
/*
**	Rotation
*/
void			v3rotate(t_vec3 *a, t_vec3 b);
void			v3rotate3(t_vec3 *v, double x, double y, double z);
void			v3rotatex(t_vec3 *v, double o);
void			v3rotatey(t_vec3 *v, double o);
void			v3rotatez(t_vec3 *v, double o);
void			v3rotateaxis(t_vec3 *a, t_vec3 u, double ro);
/*
**	Misc
*/
int		v3intrange(t_vec3 v, int min, int max);
int		v3drange(t_vec3 v, double min, double max);
#endif
