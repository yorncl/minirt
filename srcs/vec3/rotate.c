/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mclaudel <mclaudel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/23 19:19:28 by mclaudel          #+#    #+#             */
/*   Updated: 2019/11/23 19:19:28 by mclaudel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vec3.h>

void	v3rotate(vec3 *a, vec3 *b);
void	v3rotate3(vec3 *v, double x, double y, double z);
void	v3rotateX(vec3 *v, double x);
void	v3rotateY(vec3 *v, double y);
void	v3rotateZ(vec3 *v, double z);